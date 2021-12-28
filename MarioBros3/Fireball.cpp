#include "Fireball.h"
#include "Mario.h"

CFireball::CFireball(float x, float y, Area playerArea)
{
	this->x = x;
	this->y = y;
	SetRoute(playerArea);
}

void CFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_BBOX_WIDTH / 2;
	top = y - FIREBALL_BBOX_HEIGHT / 2;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y > CGame::GetInstance()->GetCamPosY() + GAME_SCREEN_HEIGHT || y < CGame::GetInstance()->GetCamPosY())
		isDeleted = true;

	if (effects.empty())
	{
		x += vx * dt;
		y += vy * dt;
	}

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Update(dt, coObjects);

		if (effects[i]->IsDeleted())
			effects.erase(effects.begin() + i);
	}

	float ml, mt, mr, mb, pl, pt, pr, pb;
	GetBoundingBox(ml, mt, mr, mb);
	CMario::GetInstance()->GetBoundingBox(pl, pt, pr, pb);
	if (CGameObject::CheckAABB(ml, mt, mr, mb, pl, pt, pr, pb) && !CMario::GetInstance()->GetUntouchable())
	{
		CreateEffect();
		CMario::GetInstance()->HitByEnemy();
	}
}

void CFireball::Render()
{
	if (vx > 0)
		CAnimations::GetInstance()->Get(ID_ANI_FIREBALL_RIGHT)->Render(x, y);
	else
		CAnimations::GetInstance()->Get(ID_ANI_FIREBALL_LEFT)->Render(x, y);

	for (LPGAMEOBJECT effect : effects)
		effect->Render();

	//RenderBoundingBox();
}

void CFireball::CreateEffect()
{
	CHitEffect* effect = new CHitEffect(x, y); // chỉnh lại x, y
	effects.push_back(effect);
}

void CFireball::SetRoute(Area playerArea)
{
	switch (playerArea)
	{
	case Area::TOP_LEFT_FAR:
		vx = -FIREBALL_SPEED_X;
		vy = vx / FIREBALL_SPEED_Y_DIVISOR;
		break;
	case Area::TOP_LEFT_NEAR:
		vx = -FIREBALL_SPEED_X;
		vy = vx;
		break;
	case Area::TOP_RIGHT_FAR:
		vx = FIREBALL_SPEED_X;
		vy = -vx / FIREBALL_SPEED_Y_DIVISOR;
		break;
	case Area::TOP_RIGHT_NEAR:
		vx = FIREBALL_SPEED_X;
		vy = -vx;
		break;
	case Area::BOTTOM_LEFT_FAR:
		vx = -FIREBALL_SPEED_X;
		vy = -vx / FIREBALL_SPEED_Y_DIVISOR;
		break;
	case Area::BOTTOM_LEFT_NEAR:
		vx = -FIREBALL_SPEED_X;
		vy = -vx;
		break;
	case Area::BOTTOM_RIGHT_FAR:
		vx = FIREBALL_SPEED_X;
		vy = vx / FIREBALL_SPEED_Y_DIVISOR;
		break;
	case Area::BOTTOM_RIGHT_NEAR:
		vx = FIREBALL_SPEED_X;
		vy = vx;
		break;
	}
}
