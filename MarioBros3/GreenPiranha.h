#pragma once
#include "GameObject.h"
#include "Mario.h"



class CGreenPiranha : public CGameObject
{
	CTimer* attackTime = new CTimer(GREEN_PIRANHA_DELAY_TIME);
	CTimer* sleepTime = new CTimer(GREEN_PIRANHA_DELAY_TIME);
	CTimer* deadTime = new CTimer(PIRANHA_MAX_EXISTING_TIME_AFTER_DEATH);

	bool vanish;

	CMario* player;

public:
	CGreenPiranha(float x, float y, Type type);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	bool CheckPlayerInSafeZone(float pl, float pt, float pr, float pb);
};

