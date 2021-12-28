#include "HitEffect.h"

void CHitEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (effectTime->IsTimeUp())
		isDeleted = true;
}

void CHitEffect::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_HIT_EFFECT)->Render(x, y);
}
