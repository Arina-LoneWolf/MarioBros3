#include "P_Switch.h"
#include "MagicCoinBrick.h"
#include "Mario.h"

void CP_Switch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float ml, mt, mr, mb, pl, pt, pr, pb;
	GetBoundingBox(ml, mt, mr, mb);
	CMario::GetInstance()->GetBoundingBox(pl, pt, pr, pb);
	if (CGameObject::CheckAABB(ml, mt, mr, mb, pl, pt, pr, pb) && CMario::GetInstance()->GetSpeedY() > 0)
	{
		CMario::GetInstance()->SetSpeedY(-MARIO_JUMP_DEFLECT_SPEED);
		SetState(P_SWITCH_STATE_PRESSED);
	}
}

void CP_Switch::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (state == P_SWITCH_STATE_PRESSED)
		animations->Get(ID_ANI_P_SWITCH_PRESSED)->Render(x, y);
	else
		animations->Get(ID_ANI_P_SWITCH_NORMAL)->Render(x, y);

	//RenderBoundingBox();
}

void CP_Switch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == P_SWITCH_STATE_PRESSED) return;

	left = x - P_SWITCH_BBOX_WIDTH / 2;
	top = y - P_SWITCH_BBOX_HEIGHT / 2;
	right = left + P_SWITCH_BBOX_WIDTH;
	bottom = top + P_SWITCH_BBOX_HEIGHT;
}

void CP_Switch::SetState(int state)
{
	if (state == P_SWITCH_STATE_PRESSED)
	{
		for (UINT i = 0; i < magicCoinBricks->size(); i++)
			magicCoinBricks->at(i)->SetState(MAGIC_COIN_BRICK_STATE_TRANSFORM);
	}

	CGameObject::SetState(state);
}
