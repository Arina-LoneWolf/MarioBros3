#pragma once
#include "GameObject.h"

class CDetectionBox : public CGameObject
{
	CDetectionBox() {}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
};

