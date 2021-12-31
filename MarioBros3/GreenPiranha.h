#pragma once
#include "GameObject.h"
#include "Mario.h"

#define GREEN_PIRANHA_DELAY_TIME 820

#define GREEN_PIRANHA_SPEED_Y 0.06f

#define GREEN_PIRANHA_SAFE_ZONE_RIGHT	1827
#define GREEN_PIRANHA_SAFE_ZONE_LEFT	1788
#define GREEN_PIRANHA_SAFE_ZONE_BOTTOM	415

#define GREEN_PIRANHA_BBOX_WIDTH	16
#define GREEN_PIRANHA_BBOX_HEIGHT	24

#define GREEN_PIRANHA_STATE_MOVE_UP		10
#define GREEN_PIRANHA_STATE_MOVE_DOWN	11
#define GREEN_PIRANHA_STATE_DIE			19

#define ID_ANI_GREEN_PIRANHA 730

class CGreenPiranha : public CGameObject
{
	CTimer* attackTime = new CTimer(GREEN_PIRANHA_DELAY_TIME);
	CTimer* sleepTime = new CTimer(GREEN_PIRANHA_DELAY_TIME);

	CMario* player;

	float topLimit;
	float bottomLimit;

public:
	CGreenPiranha(float x, float y, Type type, CMario* player);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
	bool CheckPlayerInSafeZone(float pl, float pt, float pr, float pb);
};

