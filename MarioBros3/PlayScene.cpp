#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Ground.h"
#include "PandoraBrick.h"
#include "Pipe.h"
#include "FirePiranha.h"
#include "GreenPiranha.h"
#include "HiddenPortal.h"
#include "Koopa.h"
#include "Goomba.h"
#include "MagicCoinBrick.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	map = NULL;
	HUD = NULL;
	cam = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_TILEMAP 7

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

#define CAM_START_Y	238.0f

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[static_cast<int64_t>(i)+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	Type object_type = static_cast<Type>(atoi(tokens[0].c_str()));
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;
	CMagicCoinBrick* magicCoinBrick = NULL;

	switch (object_type)
	{
	case Type::MARIO:
		if (player != NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = CMario::GetInstance();
		player = (CMario*)obj;
		player->SetPosition(x, y);
		cam = new Camera(player);

		DebugOut(L"[INFO] Player object has been created!\n");
		break;

	case Type::YELLOW_GOOMBA:
	case Type::RED_PARAGOOMBA:
		obj = new CGoomba(x, y, object_type); break;

	case Type::RED_KOOPA:
	case Type::GREEN_KOOPA:
	case Type::GREEN_PARAKOOPA:
		obj = new CKoopa(x, y, object_type, (CMario*)player); break;

	case Type::COIN:
	case Type::BRONZE_BRICK:
		magicCoinBrick = new CMagicCoinBrick(x, y, object_type); break;

	case Type::PANDORA_BRICK:
	{
		int brickType = atoi(tokens[3].c_str());
		int itemType = atoi(tokens[4].c_str());

		obj = new CPandoraBrick(x, y, object_type, brickType, itemType, &magicCoinBricks);

		break;
	}

	case Type::PIPE:
	{
		int pipeType = atoi(tokens[3].c_str());
		obj = new CPipe(x, y, object_type, pipeType);

		break;
	}

	case Type::RED_FIRE_PIRANHA:
	case Type::GREEN_FIRE_PIRANHA:
		obj = new CFirePiranha(x, y, object_type, (CMario*)player); break;

	case Type::GREEN_PIRANHA:
		obj = new CGreenPiranha(x, y, object_type, (CMario*)player); break;

	case Type::COLOR_BOX:
	case Type::GROUND:
	{
		int row_cell_num = atoi(tokens[3].c_str());
		int column_cell_num = atoi(tokens[4].c_str());

		obj = new CGround(x, y, object_type, row_cell_num, column_cell_num);

		break;
	}

	case Type::HIDDEN_PORTAL:
	{
		int portalType = atoi(tokens[3].c_str());
		obj = new CHiddenPortal(x, y, object_type, portalType,player);

		break;
	}

	case Type::PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());

		obj = new CPortal(x, y, r, b, scene_id);

		break;
	}

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	if (magicCoinBrick)
		magicCoinBricks.push_back(magicCoinBrick);
	else
		objects.push_back(obj);
}

void CPlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 7) return;

	int ID = atoi(tokens[0].c_str());
	wstring tileset_file_path = ToWSTR(tokens[1]);
	wstring map_file_path = ToWSTR(tokens[2]);
	int num_of_tileset_rows = atoi(tokens[3].c_str());
	int num_of_tileset_cols = atoi(tokens[4].c_str());
	int num_of_map_rows = atoi(tokens[5].c_str());
	int num_of_map_cols = atoi(tokens[6].c_str());

	map = new TileMap(ID, tileset_file_path.c_str(), map_file_path.c_str(), num_of_tileset_rows, num_of_tileset_cols, num_of_map_rows, num_of_map_cols);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[TILEMAP]") { section = SCENE_SECTION_TILEMAP; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetType() != Type::MARIO)
			coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < magicCoinBricks.size(); i++)
	{
		coObjects.push_back(magicCoinBricks[i]);
	}

	for (size_t i = 0; i < magicCoinBricks.size(); i++)
	{
		magicCoinBricks[i]->Update(dt, &coObjects);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	cam->Update(dt);

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	//cy = CAM_START_Y;
	//cy -= game->GetBackBufferHeight() / 2;
	//if ((player->IsOnPowerMode() && player->GetLevel() == MARIO_LEVEL_RACCOON) || player->GetPosY() < 248 || player->GetSpeedY() > 0)
	//{
	//	/*if (player->GetSpeedY() < 0 && player->GetPosY() < (game->GetCamPosY() + GAME_SCREEN_HEIGHT / 2 - 32))
	//		cy -= game->GetBackBufferHeight() / 2;
	//	else if (player->GetSpeedY() > 0 && player->GetPosY() < game->GetCamPosY() + GAME_SCREEN_HEIGHT / 2 + 32)
	//		cy -= game->GetBackBufferHeight() / 2;*/
	//	cy -= game->GetBackBufferHeight() / 2;
	//}

	if (cx < 0) cx = 0;
	if (cx > map->GetMapWidth() - GAME_SCREEN_WIDTH) cx = (float)map->GetMapWidth() - GAME_SCREEN_WIDTH;

	/*if (cy < 0) cy = 0;
	if (cy > CAM_START_Y) cy = CAM_START_Y;*/


	//CGame::GetInstance()->SetCamPos(cx, CAM_START_Y /*cy*/);
	//CGame::GetInstance()->SetCamPos(cx, cy);
	CGame::GetInstance()->SetCamPosX(cx);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	map->Render();

	for (size_t i = 0; i < magicCoinBricks.size(); i++)
		magicCoinBricks[i]->Render();

	for (int i = objects.size() - 1; i >= 0; i--)
		objects[i]->Render();

	HUD->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();

	for (it = magicCoinBricks.begin(); it != magicCoinBricks.end(); it++)
	{
		delete (*it);
	}
	magicCoinBricks.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	/*for (int i = 0; i < magicCoinBricks.size(); i++)
		delete magicCoinBricks[i];

	magicCoinBricks.clear();*/
	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	for (it = magicCoinBricks.begin(); it != magicCoinBricks.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());

	magicCoinBricks.erase(
		std::remove_if(magicCoinBricks.begin(), magicCoinBricks.end(), CPlayScene::IsGameObjectDeleted),
		magicCoinBricks.end());
}