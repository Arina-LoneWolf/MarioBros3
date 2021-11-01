#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.035f

#define GOOMBA_DIE_TIMEOUT 300

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200


#pragma region GOOMBA_BBOX_SIZE

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_DIE_BBOX_HEIGHT 8

#define PARAGOOMBA_BBOX_WIDTH 20
#define PARAGOOMBA_BBOX_HEIGHT 15

#define GOOMBA_DIE_OFFSET_LEFT 7
#define GOOMBA_DIE_OFFSET_TOP 1
#define GOOMBA_DIE_OFFSET_Y 2
#define GOOMBA_WALKING_OFFSET_TOP 8
#define PARAGOOMBA_DIE_OFFSET_TOP 5

#pragma endregion

#pragma region GOOMBA_ANIMATION_ID

#define ID_ANI_GOOMBA_WALKING		702
#define ID_ANI_GOOMBA_DIE_BY_CRUSH	703
#define ID_ANI_GOOMBA_DIE_BY_ATTACK	704

#define ID_ANI_PARAGOOMBA_WINGS_WALKING 705
#define ID_ANI_PARAGOOMBA_NORMAL_WALKING 708
#define ID_ANI_PARAGOOMBA_FLAP_WINGS_QUICKLY 706
#define ID_ANI_PARAGOOMBA_FLAP_WINGS_SLOWLY	707
#define ID_ANI_PARAGOOMBA_DIE_BY_CRUSH 709
#define ID_ANI_PARAGOOMBA_DIE_BY_ATTACK 750

#pragma endregion

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y);
	virtual void SetState(int state);
};