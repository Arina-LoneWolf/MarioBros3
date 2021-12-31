#pragma once
#include "GameObject.h"

#define MAP_POINT_BBOX_WIDTH	4
#define MAP_POINT_BBOX_HEIGHT	4

class CMapPoint : public CGameObject
{
public:
	float leftEdge, topEdge, rightEdge, bottomEdge;
	int sceneID;
	int id;
	vector<bool> hasPointAround;

	CMapPoint(float x, float y, Type type, int sceneID, bool left, bool right, bool above, bool under, int id);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	bool HasPortal() { return !sceneID; }
	~CMapPoint() {}
};

