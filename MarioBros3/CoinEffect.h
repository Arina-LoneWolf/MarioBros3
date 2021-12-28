#pragma once
#include "GameObject.h"

#define COIN_EFFECT_SPEED_Y 0.14f

#define COIN_EFFECT_HIGHEST_POS_OFFSET 65
#define COIN_EFFECT_LOWEST_POS_OFFSET 20

#define ID_ANI_COIN_EFFECT 903

class CCoinEffect : public CGameObject
{
	float highestPos;
	float lowestPos;
public:
	CCoinEffect(float x, float y, Type type) : CGameObject(x, y, type)
	{
		highestPos = y - COIN_EFFECT_HIGHEST_POS_OFFSET;
		lowestPos = y - COIN_EFFECT_LOWEST_POS_OFFSET;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = t = r = b = 0; }
};

