#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

#include "HiddenPortal.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	/*case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;*/
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_ATTACK);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_4:
		mario->SetLevel(MARIO_LEVEL_FIRE);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if (mario->GetState() != MARIO_STATE_GO_IN_PIPE && mario->GetState() != MARIO_STATE_GO_OUT_PIPE)
			mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		if (mario->GetState() != MARIO_STATE_GO_IN_PIPE && mario->GetState() != MARIO_STATE_GO_OUT_PIPE)
			mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		//DebugOut(L"CHAM PORTAL %d\n", mario->GetCollisionWithHiddenPortal());
		if (mario->GetCollisionWithHiddenPortal() == HIDDEN_ZONE_ENTRANCE_START)
			mario->SetState(MARIO_STATE_GO_IN_PIPE);
		else
			mario->SetState(MARIO_STATE_SIT);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		if (game->IsKeyDown(DIK_S))
			mario->SetState(MARIO_STATE_GO_OUT_PIPE);
	}
	else
	{
		/*DebugOut(L"mario state %d\n", mario->GetState());*/
		if (mario->GetState() != MARIO_STATE_GO_IN_PIPE && mario->GetState() != MARIO_STATE_GO_OUT_PIPE)
		{
			//DebugOut(L"SET IDLE\n");
			mario->SetState(MARIO_STATE_IDLE);
		}
	}
}