#pragma once
#include "GameObject.h"

#define CELL_WIDTH	136
#define CELL_HEIGHT	132

#define MAP_WIDTH	2832
#define MAP_HEIGHT	736

class CGrid
{
	vector<vector<vector<LPGAMEOBJECT>>> cells;
public:
	CGrid();
	~CGrid();
	void Resize();
	void Clear(int numRow, int numCol);
	void Push(LPGAMEOBJECT obj, int row, int col);
	void Update(vector<LPGAMEOBJECT> listObj);
	void Get(vector<LPGAMEOBJECT>& listObj);
	void MakeObjectsOutCam(vector<LPGAMEOBJECT>& listObj);
};

