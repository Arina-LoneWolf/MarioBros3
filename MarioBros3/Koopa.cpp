#include "Koopa.h"
#include "debug.h"
#include "DetectionBox.h"
#include "Goomba.h"

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPA_BBOX_WIDTH / 2;
	right = left + KOOPA_BBOX_WIDTH;

	if (state == KOOPA_STATE_WALKING)
	{
		top = y - KOOPA_BBOX_HEIGHT / 2;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		top = y - KOOPA_SHELL_OFFSET_TOP;
		bottom = top + KOOPA_SHELL_BBOX_HEIGHT;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	for (int i = 0; i < subItems.size(); i++)
	{
		subItems[i]->Update(dt, coObjects);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;

	if (state == KOOPA_STATE_SHELL)
		aniId = ID_ANI_KOOPA_SHELL_PRONE;
	else if (state == KOOPA_STATE_SHELL_MOVING)
		aniId = ID_ANI_KOOPA_SHELL_MOVING_PRONE;
	else
	{
		if (nx > 0)
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		else
			aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

	for (int i = 0; i < subItems.size(); i++)
	{
		subItems[i]->Render();
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = -vx;
		nx = -nx;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (e->nx != 0)
	{
		goomba->SetNx(nx);
		goomba->SetState(GOOMBA_STATE_DIE_BY_ATTACK);
	}
}

CKoopa::CKoopa(float x, float y)
{
	ax = 0.0f;
	ay = 0.0006f;
	SetState(KOOPA_STATE_WALKING);
	CDetectionBox* detectionBox = new CDetectionBox(this);
	subItems.push_back(detectionBox);
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case KOOPA_STATE_WALKING:
		vx = -0.035f;
		nx = -1;
		break;

	case KOOPA_STATE_SHELL:
		vx = 0;
		break;

	case KOOPA_STATE_SHELL_MOVING:
		vx = 0.16f * nx;
		break;
	}
}

void CKoopa::ChangeDirection()
{
	if (state == KOOPA_STATE_WALKING)
	{
		vx = -vx;
		nx = -nx;
	}
}
