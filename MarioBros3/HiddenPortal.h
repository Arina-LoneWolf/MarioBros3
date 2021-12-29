#pragma once
#include "GameObject.h"

#define HIDDEN_PORTAL_BBOX_WIDTH 32
#define HIDDEN_PORTAL_BBOX_HEIGHT 2

#define NONE						0
#define HIDDEN_ZONE_ENTRANCE_START	1
#define HIDDEN_ZONE_ENTRANCE_END	2
#define HIDDEN_ZONE_EXIT_START		3
#define HIDDEN_ZONE_EXIT_END		4

class CHiddenPortal : public CGameObject
{
	int portalType;

public:
	CHiddenPortal(float x, float y, Type type, int portalType) : CGameObject(x, y, type)
	{
		this->portalType = portalType;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

