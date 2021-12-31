#include "Camera.h"

#define MARIO_GO_OUT_PIPE_POS_X	2331
#define MARIO_GO_OUT_PIPE_POS_Y	399

#define MARIO_GO_IN_PIPE_POS_X	2105
#define MARIO_GO_IN_PIPE_POS_Y	481

#define STANDARD_ALTITUDE	260

#define HIDDEN_ZONE_CAM_Y	464

void Camera::Update(DWORD dt)
{
	float pl, pt, pr, pb;
	player->GetBoundingBox(pl, pt, pr, pb);

	CGame* game = CGame::GetInstance();

	if (player->GetState() == MARIO_STATE_GO_OUT_PIPE && !player->atHiddenPortal && isInHiddenZone)
	{
		camY = CAMERA_INITIAL_Y;
		player->SetPosition(MARIO_GO_OUT_PIPE_POS_X, MARIO_GO_OUT_PIPE_POS_Y);
		isInHiddenZone = false;
	}

	if (isInHiddenZone) return;

	if (player->GetState() == MARIO_STATE_GO_IN_PIPE && !player->atHiddenPortal)
	{
		player->SetPosition(MARIO_GO_IN_PIPE_POS_X, MARIO_GO_IN_PIPE_POS_Y);
		game->SetCamPosY(HIDDEN_ZONE_CAM_Y);
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
		if (player->vy < 0 && pt < camY + GAME_SCREEN_HEIGHT / 3 && camY <= CAMERA_INITIAL_Y && player->y < STANDARD_ALTITUDE)
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
