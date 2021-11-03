#include "Mushroom.h"
#include "debug.h"
#include "Mario.h"

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + 16;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y < highestPos)
	{
		y = highestPos;
		ay = 0.0004f;
		//vx = -0.035f;
		vx = -0.07f;
	}

	float ml, mt, mr, mb, pl, pt, pr, pb;
	GetBoundingBox(ml, mt, mr, mb);
	CMario::GetInstance()->GetBoundingBox(pl, pt, pr, pb);
	if (CGameObject::CheckAABB(ml, mt, mr, mb, pl, pt, pr, pb))
	{
		CMario::GetInstance()->SetLevel(MARIO_LEVEL_BIG);
		isDeleted = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SUPER_MUSHROOM)->Render(x, y);

	RenderBoundingBox();
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::SetState(int state)
{
}
