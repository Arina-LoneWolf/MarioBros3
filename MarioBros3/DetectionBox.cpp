#include "DetectionBox.h"
#include "debug.h"

void CDetectionBox::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float x, y;
	koopa->GetPosition(x, y);

	if (koopa->GetNx() > 0)
		left = x + 2;
	else
		left = x - 4;

	top = y - 8;
	right = left + 2;
	bottom = top + 28;
}

void CDetectionBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float ml, mt, mr, mb, bl, bt, br, bb; // main object (m) and blocking objects (b)
	GetBoundingBox(ml, mt, mr, mb);

	bool noCollision = true;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<CKoopa*>(e)) continue;

		e->GetBoundingBox(bl, bt, br, bb);
		if (CGameObject::CheckAABB(ml, mt, mr, mb, bl, bt, br, bb))
		{
			noCollision = false;
			break;
		}
	}

	if (noCollision && koopa->GetState() == KOOPA_STATE_WALKING)
		koopa->ChangeDirection();
}

void CDetectionBox::Render()
{
	RenderBoundingBox();
}
