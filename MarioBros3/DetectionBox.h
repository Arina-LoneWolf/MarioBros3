#pragma once
#include "GameObject.h"
#include "Koopa.h"

class CDetectionBox : public CGameObject
{
public:
	CKoopa* koopa;

	CDetectionBox(CKoopa* koopa) { this->koopa = koopa; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

