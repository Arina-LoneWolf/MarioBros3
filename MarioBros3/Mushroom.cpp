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
	

	if (y < highestPos)
	{
		y = highestPos;
		ay = 0.001f;
		//ay = 0.15f;
		vx = -0.035f;
		//vx = -0.07f;
		//vx = -0.07f;
	}

	float ml, mt, mr, mb, pl, pt, pr, pb;
	GetBoundingBox(ml, mt, mr, mb);
	CMario::GetInstance()->GetBoundingBox(pl, pt, pr, pb);
	if (CGameObject::CheckAABB(ml, mt, mr, mb, pl, pt, pr, pb))
	{
		CMario::GetInstance()->SetLevel(MARIO_LEVEL_BIG);
		isDeleted = true;
	}

	//CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	vy += ay * dt;
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
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		
		if (e->ny < 0) vy = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		DebugOut(L"CHAM DOI CHIEU NAM\n");
		vx = -vx;
	}
}

void CMushroom::SetState(int state)
{
}
