#include "PandoraBrick.h"

void CPandoraBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	
	if (state == PANDORA_BRICK_STATE_ACTIVE)
		animations->Get(ID_ANI_NORMAL_BRICK)->Render(x, y);
	else
	{
		if (brickType == QUESTION_BRICK_TYPE)
			animations->Get(ID_ANI_QUESTION_BRICK)->Render(x, y);
		else
			animations->Get(ID_ANI_BRONZE_BRICK)->Render(x, y);
	}

	RenderBoundingBox();
}

void CPandoraBrick::Update(DWORD dt)
{
	CGameObject::Update(dt);

	y += vy * dt;

	if (state == PANDORA_BRICK_STATE_ACTIVE && y <= highestPos)
	{
		vy = -vy;
	}

	if (vy > 0 && y >= initialY)
	{
		vy = 0;
		y = initialY;
		isReadyToDropItem = true;
	}
}

void CPandoraBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PANDORA_BRICK_BBOX_WIDTH / 2;
	t = y - PANDORA_BRICK_BBOX_HEIGHT / 2;
	r = l + PANDORA_BRICK_BBOX_WIDTH;
	b = t + PANDORA_BRICK_BBOX_HEIGHT;
}

void CPandoraBrick::SetState(int state)
{
	CGameObject::SetState(state);

	if (state == PANDORA_BRICK_STATE_ACTIVE)
	{
		vy = -PANDORA_BRICK_BOUNCE_SPEED_Y;
	}
}
