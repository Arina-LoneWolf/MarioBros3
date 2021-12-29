#include "HiddenPortal.h"
#include "Mario.h"

void CHiddenPortal::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HIDDEN_PORTAL_BBOX_WIDTH / 2;
	top = y - HIDDEN_PORTAL_BBOX_HEIGHT / 2;
	right = left + HIDDEN_PORTAL_BBOX_WIDTH;
	bottom = top + HIDDEN_PORTAL_BBOX_HEIGHT;
}

void CHiddenPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float ml, mt, mr, mb, pl, pt, pr, pb;
	GetBoundingBox(ml, mt, mr, mb);
	CMario::GetInstance()->GetBoundingBox(pl, pt, pr, pb);
	if (CGameObject::CheckAABB(ml, mt, mr, mb, pl, pt, pr, pb))
		CMario::GetInstance()->SetCollisionWithHiddenPortal(portalType);
	else
		CMario::GetInstance()->SetCollisionWithHiddenPortal(NONE);
}

void CHiddenPortal::Render()
{
	RenderBoundingBox();
}
