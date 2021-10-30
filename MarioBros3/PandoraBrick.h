#pragma once

#include "GameObject.h"

#define QUESTION_BRICK_TYPE 1
#define DISGUISED_BRONZE_BRICK_TYPE 2

#define PANDORA_BRICK_BBOX_WIDTH 16
#define PANDORA_BRICK_BBOX_HEIGHT 16

#define PANDORA_BRICK_BOUNCE_DISTANCE 10
#define PANDORA_BRICK_BOUNCE_SPEED_Y 0.1f

#define PANDORA_BRICK_STATE_ACTIVE 101

#define ID_ANI_QUESTION_BRICK	602
#define ID_ANI_NORMAL_BRICK	603
#define ID_ANI_BRONZE_BRICK	612 // coi sửa lại id cho đúng

class CPandoraBrick : public CGameObject {
public:
	int brickType;
	int itemType;
	int initialY;
	int highestPos;

	bool isReadyToDropItem;

	CPandoraBrick(float x, float y, int brickType, int itemType) : CGameObject(x, y) {
		this->brickType = brickType;
		this->itemType = itemType;
		initialY = y;
		highestPos = initialY - PANDORA_BRICK_BOUNCE_DISTANCE;
	}
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};

