#include "WorldMap.h"
#include "WorldMapKeyHandler.h"
#include "MapPoint.h"
#include "MapObject.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_TILEMAP 7

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CWorldMap::_ParseSection_SPRITES(string line)
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

void CWorldMap::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[static_cast<int64_t>(i) + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CWorldMap::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CWorldMap::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	Type object_type = static_cast<Type>(atoi(tokens[0].c_str()));
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;
	CMapPoint* point = NULL;

	switch (object_type)
	{
	case Type::MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		//obj = CMario::GetInstance();
		//player = (CMario*)obj;
		player = CMario::GetInstance();
		player->SetPosition(x, y);
		player->isOnWorldMap = 1;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;

	case Type::MAP_POINT:
	{
		int sceneID = atoi(tokens[4].c_str());
		int l = atoi(tokens[5].c_str());
		int r = atoi(tokens[6].c_str());
		int a = atoi(tokens[7].c_str());
		int u = atoi(tokens[8].c_str());
		int id = atoi(tokens[9].c_str());
		point = new CMapPoint(x, y, object_type, sceneID, l, r, a, u, id);
		break;
	}

	case Type::TUSSOCK:
	case Type::HELP_BUBBLE:
	case Type::GATEKEEPER:
	{
		obj = new CMapObject(x, y, object_type);
		break;
	}

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	if (point)
		points.push_back(point);
	else if (obj)
		objects.push_back(obj);
}

void CWorldMap::_ParseSection_TILEMAP(string line)
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

void CWorldMap::LoadAssets(LPCWSTR assetFile)
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

CWorldMap::CWorldMap(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	map = NULL;
	HUD = NULL;
	key_handler = new CWorldMapKeyHandler(this);
}

void CWorldMap::Load()
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

void CWorldMap::Update(DWORD dt)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i]->Update(dt, &points);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &objects);
	}

	if (player == NULL) return;

	player->UpdateOnWorldMap(dt, &points);
}

void CWorldMap::Render()
{
	map->Render();

	for (size_t i = 0; i < objects.size(); i++)
		objects[i]->Render();

	for (size_t i = 0; i < points.size(); i++)
		points[i]->Render();

	player->RenderOnWorldMap();

	HUD->Render();
}

void CWorldMap::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	for (int i = 0; i < points.size(); i++)
		delete points[i];

	points.clear();
	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}
