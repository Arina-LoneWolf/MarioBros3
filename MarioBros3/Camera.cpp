#include "Camera.h"

void Camera::Update(DWORD dt)
{
	float pl, pt, pr, pb;
	player->GetBoundingBox(pl, pt, pr, pb);

	CGame* game = CGame::GetInstance();

	if (player->GetState() == MARIO_STATE_GO_OUT_PIPE && !player->atHiddenPortal && isInHiddenZone)
	{
		camY = CAMERA_INITIAL_Y;
		player->SetPosition(2335, 399);
		isInHiddenZone = false;
		//return;
	}

	if (isInHiddenZone) return;

	if (player->GetState() == MARIO_STATE_GO_IN_PIPE && !player->atHiddenPortal)
	{
		player->SetPosition(2105, 481);
		game->SetCamPosY(464);
		isInHiddenZone = true;
	}

	if (player->GetState() == MARIO_STATE_GO_IN_PIPE)
		return;

	if (player->isOnPlatform)
	{
		camSpeedY = 0;
		goto SET_CAM;
	}

	if (player->IsOnPowerMode() && !player->isOnPlatform)
	{
		if (player->vy < 0 && pt < camY + GAME_SCREEN_HEIGHT / 5)
		{
			camSpeedY = player->vy;
		}
		else if (player->vy > 0 && pt > camY + GAME_SCREEN_HEIGHT / 3)
		{
			camSpeedY = player->vy;
		}
		else
			camSpeedY = 0;
	}
	else
	{
		if (player->vy < 0 && pt < camY + GAME_SCREEN_HEIGHT / 3 && camY <= CAMERA_INITIAL_Y)
		{
			camSpeedY = player->vy;
		}
		else if (player->vy > 0 && pt > camY + GAME_SCREEN_HEIGHT / 2 && camY <= CAMERA_INITIAL_Y)
			camSpeedY = player->vy;
		else
			camSpeedY = 0;
	}

SET_CAM:
	camY += camSpeedY * dt;
	if (camY < 0 || camY > CAMERA_INITIAL_Y)
		return;

	game->SetCamPosY(camY);
}
