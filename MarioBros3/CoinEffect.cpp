#include "CoinEffect.h"
#include "debug.h"

void CCoinEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (y < highestPos)
		vy = -vy;

	if (vy > 0 && y > lowestPos)
		isDeleted = true;
}

void CCoinEffect::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_COIN_EFFECT)->Render(x, y);
}
