#include "TailHitEffect.h"

void CTailHitEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (effectTime->IsTimeUp())
		isDeleted = true;
}

void CTailHitEffect::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_TAIL_HIT_EFFECT)->Render(x, y);
}
