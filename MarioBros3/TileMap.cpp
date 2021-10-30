#include "TileMap.h"

TileMap::TileMap(int ID, LPCWSTR texture_file_path, LPCWSTR data_file_path, int texture_row_cell_num, int texture_col_cell_num, int data_row_cell_num, int data_col_cell_num)
{
	this->id = ID;
	this->texture_file_path = texture_file_path;
	this->data_file_path = data_file_path;
	this->texture_row_cell_num = texture_row_cell_num;
	this->texture_col_cell_num = texture_col_cell_num;
	this->data_row_cell_num = data_row_cell_num;
	this->data_col_cell_num = data_col_cell_num;

	LoadMapResource();
	Load();
}

int TileMap::GetMapWidth()
{
	return data_col_cell_num * TILE_WIDTH;
}

void TileMap::LoadMapResource()
{
	CTextures* texture = CTextures::GetInstance();
	texture->Add(id, texture_file_path);

	LPTEXTURE texMap = texture->Get(id);

	int tileId = START_TILE_ID;
	for (UINT i = 0; i < texture_row_cell_num; i++)
	{
		for (UINT j = 0; j < texture_col_cell_num; j++)
		{
			int spriteId = id + tileId;
			sprites->Add(spriteId, TILE_WIDTH * j, TILE_HEIGHT * i, TILE_WIDTH * (j + 1), TILE_HEIGHT * (i + 1), texMap);
			tileId++;
		}
	}
}

void TileMap::Load()
{
	DebugOut(L"[INFO] Start loading map resources from : %s \n", data_file_path);

	ifstream fs(data_file_path, ios::in);

	if (fs.fail())
	{
		DebugOut(L"[ERROR] TileMap::Load_MapData failed: ID=%d", id);
		fs.close();
		return;
	}

	DebugOut(L"so dong", data_row_cell_num);
	DebugOut(L"so cot", data_col_cell_num);
	for (int i = 0; i < data_row_cell_num; i++)
	{
		for (int j = 0; j < data_col_cell_num; j++)
			fs >> tileMap[i][j];
	}

	fs.close();

	DebugOut(L"[INFO] Done loading map resources %s\n", data_file_path);
}

void TileMap::Draw()
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	int first_col = (int)cx / TILE_WIDTH;
	int last_col = first_col + (GAME_SCREEN_WIDTH / TILE_WIDTH);

	int first_row = (int)cy / TILE_HEIGHT;
	int last_row = first_row + (GAME_SCREEN_HEIGHT / TILE_HEIGHT);

	for (UINT i = first_row; i <= last_row; i++)
	{
		for (UINT j = first_col; j <= last_col; j++)
		{
			float x = TILE_WIDTH * j + TILE_WIDTH / 2;
			float y = TILE_HEIGHT * i + TILE_HEIGHT / 2;
			sprites->Get(tileMap[i][j] + id)->Draw(x, y);
		}
	}
}

TileMap::~TileMap()
{
}
