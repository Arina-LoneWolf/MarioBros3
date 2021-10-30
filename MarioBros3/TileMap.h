#pragma once
#include "Sprites.h"
#include "Textures.h"
#include "Utils.h"
#include "Game.h"
#include "debug.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

#define START_TILE_ID 1

#define SCREEN_WIDTH 759
#define SCREEN_HEIGHT 740

class TileMap
{
	CSprites* sprites = CSprites::GetInstance();
	LPCWSTR data_file_path;
	LPCWSTR texture_file_path;

	int id;
	int data_row_cell_num, data_col_cell_num;
	int texture_row_cell_num, texture_col_cell_num;

	//vector<vector<LPSPRITE>> tilemap;
	int tileMap[300][300];

public:
	TileMap(int ID, LPCWSTR texture_file_path, LPCWSTR data_file_path, int texture_row_cell_num, int texture_col_cell_num, int data_row_cell_num, int data_col_cell_num);
	int GetWidthTileMap();
	void LoadMapResource();
	void Load();
	void Draw();
	~TileMap();
};

