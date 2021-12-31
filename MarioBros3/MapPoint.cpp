#include "MapPoint.h"

CMapPoint::CMapPoint(float x, float y, Type type, int sceneID, bool left, bool right, bool above, bool under, int id) : CGameObject(x, y, type)
{
	this->id = id;
	this->x = x;
	this->y = y;
	leftEdge = x;
	topEdge = y;
	rightEdge = x + 8;
	bottomEdge = y + 8;
	this->sceneID = sceneID;
	hasPointAround.insert(hasPointAround.end(), { left, right, above, under });
}

void CMapPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x + MAP_POINT_BBOX_WIDTH / 2;
	t = y + MAP_POINT_BBOX_HEIGHT / 2;
	r = l + MAP_POINT_BBOX_WIDTH;
	b = t + MAP_POINT_BBOX_HEIGHT;
}

void CMapPoint::Render()
{
	RenderBoundingBox();
}
