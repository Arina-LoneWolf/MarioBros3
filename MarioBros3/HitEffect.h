#pragma once
#include "GameObject.h"
#include "Timer.h"

#define HIT_EFFECT_TIME 150

#define ID_ANI_HIT_EFFECT 900

class CHitEffect : public CGameObject
{
	CTimer* effectTime = new CTimer(HIT_EFFECT_TIME);

public:
	CHitEffect(float x, float y)
	{
		this->x = x;
		this->y = y;
		effectTime->Start();
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = t = r = b = 0; }
};

