#include "FirePiranha.h"
#include "Fireball.h"

CFirePiranha::CFirePiranha(float x, float y, Type type, CMario* player) : CGameObject(x, y, type)
{
	this->player = player;
	bottomLimit = y;

	if (type == Type::RED_FIRE_PIRANHA)
	{
		topLimit = y - RED_FIRE_PIRANHA_BBOX_HEIGHT;
		last_face_ani = ID_ANI_RED_FIRE_PIRANHA_FACE_DOWN_LEFT;
		last_attack_ani = ID_ANI_RED_FIRE_PIRANHA_ATTACK_DOWN_LEFT;
	}
	else
	{
		topLimit = y - GREEN_FIRE_PIRANHA_BBOX_HEIGHT;
		last_face_ani = ID_ANI_GREEN_FIRE_PIRANHA_FACE_DOWN_LEFT;
		last_attack_ani = ID_ANI_GREEN_FIRE_PIRANHA_ATTACK_DOWN_LEFT;
	}
}

void CFirePiranha::CreateFireball()
{
	Area playerArea = GetPlayerArea();
	CFireball* fireball = new CFireball(x, y, playerArea, player); // chỉnh lại x, y
	fireballs.push_back(fireball);
}

void CFirePiranha::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (type == Type::RED_FIRE_PIRANHA)
	{
		left = x - RED_FIRE_PIRANHA_BBOX_WIDTH / 2;
		top = y - RED_FIRE_PIRANHA_BBOX_HEIGHT / 2;
		right = left + RED_FIRE_PIRANHA_BBOX_WIDTH;
		bottom = top + RED_FIRE_PIRANHA_BBOX_HEIGHT;
	}
	else
	{
		left = x - GREEN_FIRE_PIRANHA_BBOX_WIDTH / 2;
		top = y - GREEN_FIRE_PIRANHA_BBOX_HEIGHT / 2;
		right = left + GREEN_FIRE_PIRANHA_BBOX_WIDTH;
		bottom = top + GREEN_FIRE_PIRANHA_BBOX_HEIGHT;
	}
}

void CFirePiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (attackTime->IsStopped() && y <= topLimit)
	{
		y = topLimit;
		vy = 0;
		attackTime->Start();
		delayToAttack->Start();
		SetState(FIRE_PIRANHA_STATE_ATTACK);
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
		SetState(FIRE_PIRANHA_STATE_MOVE_DOWN);
	}

	if (delayToAttack->IsTimeUp())
	{
		Area playerArea = GetPlayerArea();
		if (playerArea != Area::OUTSIDE_AREA)
			CreateFireball();
		delayToAttack->Stop();
	}

	if (sleepTime->IsTimeUp())
	{
		float pl, pt, pr, pb;
		player->GetBoundingBox(pl, pt, pr, pb);
		if (!CheckPlayerInSafeZone(pl, pt, pr, pb))
		{
			sleepTime->Stop();
			SetState(FIRE_PIRANHA_STATE_MOVE_UP);
		}
	}

	for (size_t i = 0; i < fireballs.size(); i++)
	{
		fireballs[i]->Update(dt, coObjects);

		if (fireballs[i]->IsDeleted())
			fireballs.erase(fireballs.begin() + i);
	}
}

void CFirePiranha::Render()
{
	Area playerArea = GetPlayerArea();

	int aniId = -1;
	
	if (state == FIRE_PIRANHA_STATE_ATTACK)
	{
		switch (playerArea)
		{
		case Area::TOP_LEFT_FAR:
		case Area::TOP_LEFT_NEAR:
			if (type == Type::RED_FIRE_PIRANHA)
				aniId = ID_ANI_RED_FIRE_PIRANHA_ATTACK_UP_LEFT;
			else
				aniId = ID_ANI_GREEN_FIRE_PIRANHA_ATTACK_UP_LEFT;
			break;
		case Area::TOP_RIGHT_FAR:
		case Area::TOP_RIGHT_NEAR:
			if (type == Type::RED_FIRE_PIRANHA)
				aniId = ID_ANI_RED_FIRE_PIRANHA_ATTACK_UP_RIGHT;
			else
				aniId = ID_ANI_GREEN_FIRE_PIRANHA_ATTACK_UP_RIGHT;
			break;
		case Area::BOTTOM_LEFT_FAR:
		case Area::BOTTOM_LEFT_NEAR:
			if (type == Type::RED_FIRE_PIRANHA)
				aniId = ID_ANI_RED_FIRE_PIRANHA_ATTACK_DOWN_LEFT;
			else
				aniId = ID_ANI_GREEN_FIRE_PIRANHA_ATTACK_DOWN_LEFT;
			break;
		case Area::BOTTOM_RIGHT_FAR:
		case Area::BOTTOM_RIGHT_NEAR:
			if (type == Type::RED_FIRE_PIRANHA)
				aniId = ID_ANI_RED_FIRE_PIRANHA_ATTACK_DOWN_RIGHT;
			else
				aniId = ID_ANI_GREEN_FIRE_PIRANHA_ATTACK_DOWN_RIGHT;
			break;
		case Area::OUTSIDE_AREA:
			aniId = last_attack_ani;
			break;
		}
		last_attack_ani = aniId;
	}
	else
	{
		switch (playerArea)
		{
		case Area::TOP_LEFT_FAR:
		case Area::TOP_LEFT_NEAR:
			aniId = ID_ANI_RED_FIRE_PIRANHA_FACE_UP_LEFT;
			break;
		case Area::TOP_RIGHT_FAR:
		case Area::TOP_RIGHT_NEAR:
			aniId = ID_ANI_RED_FIRE_PIRANHA_FACE_UP_RIGHT;
			break;
		case Area::BOTTOM_LEFT_FAR:
		case Area::BOTTOM_LEFT_NEAR:
			aniId = ID_ANI_RED_FIRE_PIRANHA_FACE_DOWN_LEFT;
			break;
		case Area::BOTTOM_RIGHT_FAR:
		case Area::BOTTOM_RIGHT_NEAR:
			aniId = ID_ANI_RED_FIRE_PIRANHA_FACE_DOWN_RIGHT;
			break;
		case Area::OUTSIDE_AREA:
			aniId = last_face_ani;
			break;
		}
		last_face_ani = aniId;
	}
}

void CFirePiranha::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIRE_PIRANHA_STATE_MOVE_UP:
		vy = -FIRE_PIRANHA_SPEED_Y;
		break;
	case FIRE_PIRANHA_STATE_MOVE_DOWN:
		vy = FIRE_PIRANHA_SPEED_Y;
		break;
	case FIRE_PIRANHA_STATE_ATTACK: // this line is just for drawing
		break;
	case FIRE_PIRANHA_STATE_DIE:
		isDeleted = true;
		break;
	}
}

bool CFirePiranha::CheckPlayerInSafeZone(float pl, float pt, float pr, float pb)
{
	if (type == Type::RED_FIRE_PIRANHA)
	{
		return (pl < RED_FIRE_PIRANHA_SAFE_ZONE_RIGHT
			&& pr > RED_FIRE_PIRANHA_SAFE_ZONE_LEFT
			&& pt < RED_FIRE_PIRANHA_SAFE_ZONE_BOTTOM
			&& pb > 0);
	}
	else
	{
		return (pl < GREEN_FIRE_PIRANHA_SAFE_ZONE_RIGHT
			&& pr > GREEN_FIRE_PIRANHA_SAFE_ZONE_LEFT
			&& pt < GREEN_FIRE_PIRANHA_SAFE_ZONE_BOTTOM
			&& pb > 0);
	}
}

Area CFirePiranha::GetPlayerArea()
{
	float pl, pt, pr, pb;
	player->GetBoundingBox(pl, pt, pr, pb);
	
	if (type == Type::RED_FIRE_PIRANHA)
	{
		float separation = y + RED_FIRE_PIRANHA_BBOX_HEIGHT / 2;
		if (pb < separation)
		{
			if (pr >= RED_FIRE_PIRANHA_FAR_LEFT_START && pr < RED_FIRE_PIRANHA_NEAR_LEFT_START)
				return Area::TOP_LEFT_FAR;
			else if (pr >= RED_FIRE_PIRANHA_NEAR_LEFT_START && pr < RED_FIRE_PIRANHA_NEAR_RIGHT_START)
				return Area::TOP_LEFT_NEAR;
			else if (pr >= RED_FIRE_PIRANHA_NEAR_RIGHT_START && pr < RED_FIRE_PIRANHA_FAR_RIGHT_START)
				return Area::TOP_RIGHT_NEAR;
			else if (pr >= RED_FIRE_PIRANHA_FAR_RIGHT_START && pr <= RED_FIRE_PIRANHA_FAR_RIGHT_END)
				return Area::TOP_RIGHT_FAR;
		}
		else if (pb >= separation)
		{
			if (pr >= RED_FIRE_PIRANHA_FAR_LEFT_START && pr < RED_FIRE_PIRANHA_NEAR_LEFT_START)
				return Area::BOTTOM_LEFT_FAR;
			else if (pr >= RED_FIRE_PIRANHA_NEAR_LEFT_START && pr < RED_FIRE_PIRANHA_NEAR_RIGHT_START)
				return Area::BOTTOM_LEFT_NEAR;
			else if (pr >= RED_FIRE_PIRANHA_NEAR_RIGHT_START && pr < RED_FIRE_PIRANHA_FAR_RIGHT_START)
				return Area::BOTTOM_RIGHT_NEAR;
			else if (pr >= RED_FIRE_PIRANHA_FAR_RIGHT_START && pr <= RED_FIRE_PIRANHA_FAR_RIGHT_END)
				return Area::BOTTOM_RIGHT_FAR;
		}
	}
	else
	{
		float separation = y + GREEN_FIRE_PIRANHA_BBOX_HEIGHT / 2;
		if (pb < separation)
		{
			if (pr >= GREEN_FIRE_PIRANHA_FAR_LEFT_START && pr < GREEN_FIRE_PIRANHA_NEAR_LEFT_START)
				return Area::TOP_LEFT_FAR;
			else if (pr >= GREEN_FIRE_PIRANHA_NEAR_LEFT_START && pr < GREEN_FIRE_PIRANHA_NEAR_RIGHT_START)
				return Area::TOP_LEFT_NEAR;
			else if (pr >= GREEN_FIRE_PIRANHA_NEAR_RIGHT_START && pr < GREEN_FIRE_PIRANHA_FAR_RIGHT_START)
				return Area::TOP_RIGHT_NEAR;
			else if (pr >= GREEN_FIRE_PIRANHA_FAR_RIGHT_START && pr <= GREEN_FIRE_PIRANHA_FAR_RIGHT_END)
				return Area::TOP_RIGHT_FAR;
		}
		else if (pb >= separation)
		{
			if (pr >= GREEN_FIRE_PIRANHA_FAR_LEFT_START && pr < GREEN_FIRE_PIRANHA_NEAR_LEFT_START)
				return Area::BOTTOM_LEFT_FAR;
			else if (pr >= GREEN_FIRE_PIRANHA_NEAR_LEFT_START && pr < GREEN_FIRE_PIRANHA_NEAR_RIGHT_START)
				return Area::BOTTOM_LEFT_NEAR;
			else if (pr >= GREEN_FIRE_PIRANHA_NEAR_RIGHT_START && pr < GREEN_FIRE_PIRANHA_FAR_RIGHT_START)
				return Area::BOTTOM_RIGHT_NEAR;
			else if (pr >= GREEN_FIRE_PIRANHA_FAR_RIGHT_START && pr <= GREEN_FIRE_PIRANHA_FAR_RIGHT_END)
				return Area::BOTTOM_RIGHT_FAR;
		}
	}

	return Area::OUTSIDE_AREA;
}
