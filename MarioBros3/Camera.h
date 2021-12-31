#pragma once
#include "Mario.h"

#define CAMERA_INITIAL_Y 238.0f

class Camera
{
	float camX, camY, camSpeedY;
	CMario* player;

	CGame* game = CGame::GetInstance();
	BOOLEAN isInHiddenZone;

public:
	Camera(CMario* player)
	{
		isInHiddenZone = false;
		camX = 0.0f;
		camY = CAMERA_INITIAL_Y;
		//camY = 464;
		camSpeedY = 0;
		this->player = player;
		CGame::GetInstance()->SetCamPosY(camY);
	}

	void Update(DWORD dt);

	void SetCamPos(float x, float y) { this->camX = x; this->camY = y; }
	float GetCamPosX() { return camX; }
	float GetCamPosY() { return camY; }
	//float GetCamSpeedX() { return camSpeedX; }
	float GetCamSpeedY() { return camSpeedY; }
};

