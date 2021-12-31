#pragma once
#include "GameObject.h"

#define GATEKEEPER_SPEED_X 0.007f
#define GATEKEEPER_LEFT_LIMIT 153.0f
#define GATEKEEPER_RIGHT_LIMIT 168.0f

#define ID_ANI_TUSSOCK			5
#define ID_ANI_HELP_BUBBLE		6
#define ID_ANI_GATEKEEPER_RIGHT	7
#define ID_ANI_GATEKEEPER_LEFT	8

class CMapObject : public CGameObject
{
public:
	CMapObject(float x, float y, Type type) : CGameObject(x, y, type)
	{
		vx = -GATEKEEPER_SPEED_X;
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = t = r = b = 0; }
};