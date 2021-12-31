#include "MapObject.h"

void CMapObject::Render()
{
	int aniId = -1;

	if (type == Type::TUSSOCK)
		aniId = ID_ANI_TUSSOCK;
	else if (type == Type::HELP_BUBBLE)
		aniId = ID_ANI_HELP_BUBBLE;
	else
	{
		if (vx > 0)
			aniId = ID_ANI_GATEKEEPER_RIGHT;
		else
			aniId = ID_ANI_GATEKEEPER_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CMapObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type == Type::GATEKEEPER)
	{
		x += vx * dt;

		if ((x <= GATEKEEPER_LEFT_LIMIT && vx < 0) || (x >= GATEKEEPER_RIGHT_LIMIT && vx > 0))
			vx = -vx;
	}
}
