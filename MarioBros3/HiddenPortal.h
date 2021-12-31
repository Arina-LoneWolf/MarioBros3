#pragma once
#include "GameObject.h"
#include "Mario.h"

#define HIDDEN_PORTAL_BBOX_WIDTH 32
#define HIDDEN_PORTAL_BBOX_HEIGHT 2
#define HIDDEN_PORTAL_EXIT_START_BBOX_HEIGHT 10

#define HIDDEN_ZONE_CAM_START_X	142
#define HIDDEN_ZONE_CAM_START_Y	2191

#define NONE						0
#define HIDDEN_ZONE_ENTRANCE_START	1
#define HIDDEN_ZONE_ENTRANCE_END	2
#define HIDDEN_ZONE_EXIT_START		3
#define HIDDEN_ZONE_EXIT_END		4

class CHiddenPortal : public CGameObject
{
	/*int portalType;*/

	CMario* player;

public:
	int portalType;
	CHiddenPortal(float x, float y, Type type, int portalType, CMario* player) : CGameObject(x, y, type)
	{
		this->player = player;
		this->portalType = portalType;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	int IsBlocking() { return 0; }
};

