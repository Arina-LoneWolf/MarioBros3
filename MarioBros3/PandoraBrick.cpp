#include "PandoraBrick.h"
#include "Mario.h"
#include "Mushroom.h"
#include "CoinEffect.h"
#include "Leaf.h"
#include "P_Switch.h"

void CPandoraBrick::Render()
{
	for (int i = 0; i < backItems.size(); i++)
		backItems[i]->Render();

	CAnimations* animations = CAnimations::GetInstance();
	
	if (state == PANDORA_BRICK_STATE_ACTIVE)
		animations->Get(ID_ANI_NORMAL_BRICK)->Render(x, y);
	else
	{
		if (brickType == QUESTION_BRICK_TYPE)
			animations->Get(ID_ANI_QUESTION_BRICK)->Render(x, y);
		else
			animations->Get(ID_ANI_BRONZE_BRICK)->Render(x, y);
	}

	for (int i = 0; i < frontItems.size(); i++)
		frontItems[i]->Render();

	//RenderBoundingBox();
}

void CPandoraBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (state == PANDORA_BRICK_STATE_ACTIVE && y < highestPos && !isBouncedUp)
	{
		vy = -vy;
		isBouncedUp = true;
	}

	if (vy > 0 && y > initialY)
	{
		vy = 0;
		y = initialY;

		switch (itemType)
		{
		case ITEM_TYPE_RANDOM:
		{
			if (CMario::GetInstance()->GetLevel() == MARIO_LEVEL_SMALL)
			{
				CMushroom* mushroom = new CMushroom(x, y, Type::SUPER_MUSHROOM);
				backItems.push_back(mushroom);
			}
			else
			{
				CLeaf* leaf = new CLeaf(x, y, Type::SUPER_LEAF);
				frontItems.push_back(leaf);
			}
			break;
		}

		case ITEM_TYPE_COIN:
		{
			CCoinEffect* coin = new CCoinEffect(x, y - PANDORA_BRICK_BBOX_HEIGHT + 1, Type::COIN_EFFECT);
			frontItems.push_back(coin);
			break;
		}

		case ITEM_TYPE_GREEN_MUSHROOM:
		{
			CMushroom* mushroom = new CMushroom(x, y, Type::UP_MUSHROOM);
			backItems.push_back(mushroom);
			break;
		}

		case ITEM_TYPE_P_SWITCH:
		{
			CP_Switch* p_switch = new CP_Switch(x, y - P_SWITCH_BBOX_HEIGHT, Type::P_SWITCH, magicCoinBricks);
			backItems.push_back(p_switch);
		}

		default:
			break;
		}
	}

	for (int i = 0; i < frontItems.size(); i++)
	{
		frontItems[i]->Update(dt, coObjects);

		if (frontItems[i]->IsDeleted())
			frontItems.erase(frontItems.begin() + i);
	}

	for (int i = 0; i < backItems.size(); i++)
	{
		backItems[i]->Update(dt, coObjects);

		if (backItems[i]->IsDeleted())
			backItems.erase(backItems.begin() + i);
	}

	CGameObject::Update(dt, coObjects);
}

void CPandoraBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PANDORA_BRICK_BBOX_WIDTH / 2;
	t = y - PANDORA_BRICK_BBOX_HEIGHT / 2;
	r = l + PANDORA_BRICK_BBOX_WIDTH;
	b = t + PANDORA_BRICK_BBOX_HEIGHT;
}

void CPandoraBrick::SetState(int state)
{
	CGameObject::SetState(state);

	if (state == PANDORA_BRICK_STATE_ACTIVE)
	{
		vy = -PANDORA_BRICK_BOUNCE_SPEED_Y;
	}
}
