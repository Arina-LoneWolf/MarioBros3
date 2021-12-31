#include "HiddenPortal.h"
#include "Mario.h"

void CHiddenPortal::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HIDDEN_PORTAL_BBOX_WIDTH / 2;
	right = left + HIDDEN_PORTAL_BBOX_WIDTH;
	
	if (portalType == HIDDEN_ZONE_EXIT_START)
	{
		top = y - HIDDEN_PORTAL_EXIT_START_BBOX_HEIGHT / 2;
		bottom = top + HIDDEN_PORTAL_EXIT_START_BBOX_HEIGHT;
	}
	else
	{
		top = y - HIDDEN_PORTAL_BBOX_HEIGHT / 2;
		bottom = top + HIDDEN_PORTAL_BBOX_HEIGHT;
	}
}

void CHiddenPortal::Render()
{
	RenderBoundingBox();
}
