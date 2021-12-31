#pragma once
#include "GameObject.h"

#define P_SWITCH_BBOX_WIDTH		16
#define P_SWITCH_BBOX_HEIGHT	16

#define P_SWITCH_STATE_PRESSED	19

#define ID_ANI_P_SWITCH_NORMAL	406
#define ID_ANI_P_SWITCH_PRESSED	407

class CP_Switch : public CGameObject
{
	vector<LPGAMEOBJECT>* magicCoinBricks;

public:
	CP_Switch(float x, float y, Type type, vector<LPGAMEOBJECT>* listMagicCoinBricks) : CGameObject(x, y, type)
	{
		magicCoinBricks = listMagicCoinBricks;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};

