#pragma once
#include "GameObject.h"
#include "HitEffect.h"
#include "Mario.h"

#define FIREBALL_BBOX_WIDTH		8
#define FIREBALL_BBOX_HEIGHT	8

#define ID_ANI_FIREBALL_LEFT	890
#define ID_ANI_FIREBALL_RIGHT	891

#define FIREBALL_SPEED_X 0.05f
#define FIREBALL_SPEED_Y_DIVISOR 2.8f

class CFireball : public CGameObject
{
	vector<LPGAMEOBJECT> effects;

	CMario* player;

public:
	CFireball(float x, float y, Area playerArea, CMario* player);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void CreateEffect();
	void SetRoute(Area playerArea);
};

