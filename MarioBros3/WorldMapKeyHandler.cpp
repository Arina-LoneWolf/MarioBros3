#include "WorldMapKeyHandler.h"
#include "Mario.h"
#include "WorldMap.h"

void CWorldMapKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = (CMario*)((CWorldMap*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CWorldMapKeyHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = (CMario*)((CWorldMap*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->vx != 0 || mario->vy != 0)
		return;

	switch (KeyCode)
	{
	case DIK_LEFT:
		if (mario->movementPermission.at(ALLOWED_TO_GO_LEFT))
			mario->vx = -MARIO_SPEED_ON_MAP;
		break;
	case DIK_RIGHT:
		if (mario->movementPermission.at(ALLOWED_TO_GO_RIGHT))
			mario->vx = MARIO_SPEED_ON_MAP;
		break;
	case DIK_UP:
		if (mario->movementPermission.at(ALLOWED_TO_GO_UP))
			mario->vy = -MARIO_SPEED_ON_MAP;
		break;
	case DIK_DOWN:
		if (mario->movementPermission.at(ALLOWED_TO_GO_DOWN))
			mario->vy = MARIO_SPEED_ON_MAP;
		break;
	case DIK_S:
		CGame::GetInstance()->InitiateSwitchScene(5);
		mario->isOnWorldMap = 0;
		break;
	}
}
