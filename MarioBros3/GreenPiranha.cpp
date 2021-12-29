#include "GreenPiranha.h"

CGreenPiranha::CGreenPiranha(float x, float y, Type type, CMario* player) : CGameObject(x, y, type)
{
	this->player = player;
	bottomLimit = y;
	topLimit = y - GREEN_PIRANHA_BBOX_HEIGHT;
	SetState(GREEN_PIRANHA_STATE_MOVE_UP);
}

void CGreenPiranha::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (attackTime->IsStopped() && y <= topLimit)
	{
		y = topLimit;
		vy = 0;
		attackTime->Start();
	}
	else if (sleepTime->IsStopped() && y >= bottomLimit)
	{
		y = bottomLimit;
		vy = 0;
		sleepTime->Start();
	}

	if (attackTime->IsTimeUp())
	{
		attackTime->Stop();
		SetState(GREEN_PIRANHA_STATE_MOVE_DOWN);
	}

	if (sleepTime->IsTimeUp())
	{
		float pl, pt, pr, pb;
		player->GetBoundingBox(pl, pt, pr, pb);

		if (!CheckPlayerInSafeZone(pl, pt, pr, pb))
		{
			sleepTime->Stop();
			SetState(GREEN_PIRANHA_STATE_MOVE_UP);
		}
	}
}

void CGreenPiranha::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_GREEN_PIRANHA)->Render(x, y);
}

void CGreenPiranha::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - GREEN_PIRANHA_BBOX_WIDTH / 2;
	top = y - GREEN_PIRANHA_BBOX_HEIGHT / 2;
	right = left + GREEN_PIRANHA_BBOX_WIDTH;
	bottom = top + GREEN_PIRANHA_BBOX_HEIGHT;
}

void CGreenPiranha::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GREEN_PIRANHA_STATE_MOVE_UP:
		vy = -GREEN_PIRANHA_SPEED_Y;
		break;
	case GREEN_PIRANHA_STATE_MOVE_DOWN:
		vy = GREEN_PIRANHA_SPEED_Y;
		break;
	case GREEN_PIRANHA_STATE_DIE:
		isDeleted = true;
		break;
	}
}

bool CGreenPiranha::CheckPlayerInSafeZone(float pl, float pt, float pr, float pb)
{
	return (pl < GREEN_PIRANHA_SAFE_ZONE_RIGHT
		&& pr > GREEN_PIRANHA_SAFE_ZONE_LEFT
		&& pt < GREEN_PIRANHA_SAFE_ZONE_BOTTOM
		&& pb > 0);
}
