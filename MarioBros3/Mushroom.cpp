#include "Mushroom.h"

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CMushroom::Render()
{
}

void CMushroom::OnNoCollision(DWORD dt)
{
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

CMushroom::CMushroom(float x, float y)
{
}

void CMushroom::SetState(int state)
{
}
