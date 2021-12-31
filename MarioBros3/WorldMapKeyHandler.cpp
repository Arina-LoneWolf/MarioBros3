#include "WorldMapKeyHandler.h"
#include "Mario.h"
#include "WorldMap.h"

void CWorldMapKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = (CMario*)((CWorldMap*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CWorldMapKeyHandler::OnKeyDown(int KeyCode)
{
}
