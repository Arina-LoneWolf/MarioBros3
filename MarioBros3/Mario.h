#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include "Timer.h"
#include "Tail.h"
#include "MapPoint.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_MAX_RUNNING_SPEED	0.25f

#define MARIO_ACCEL_WALK_X	0.0003f
#define MARIO_ACCEL_RUN_X	0.0002f

#define MARIO_DECEL_X	0.00025f

#define MARIO_JUMP_SPEED_Y		0.34f
#define MARIO_JUMP_RUN_SPEED_Y	0.39f
#define MARIO_GO_PIPE_SPEED_Y	0.03f
#define MARIO_FLYING_SPEED_Y	0.25f

#define MARIO_GRAVITY			0.0008f
#define MARIO_WAG_TAIL_GRAVITY	0.000035f
#define MARIO_POWER_GRAVITY		0.0003f

#define MARIO_JUMP_DEFLECT_SPEED  0.2f

#define GROUND_Y 160.0f

#define MARIO_WORLD_MAP_BBOX	16

#pragma region MARIO_STATE

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define	MARIO_STATE_ATTACK			700

#define MARIO_STATE_GO_IN_PIPE		800
#define MARIO_STATE_GO_OUT_PIPE		801

#define MARIO_STATE_RELEASE_SHELL	810

#pragma endregion

#pragma region MARIO_ANIMATION_ID

// BIG
#define ID_ANI_MARIO_IDLE_RIGHT 100
#define ID_ANI_MARIO_IDLE_LEFT 120

#define ID_ANI_MARIO_WALKING_RIGHT 101
#define ID_ANI_MARIO_WALKING_LEFT 121

#define ID_ANI_MARIO_RUNNING_RIGHT 102
#define ID_ANI_MARIO_RUNNING_LEFT 122

#define ID_ANI_MARIO_FALLING_RIGHT 106
#define ID_ANI_MARIO_FALLING_LEFT 126

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 103
#define ID_ANI_MARIO_JUMP_WALK_LEFT 123

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 111
#define ID_ANI_MARIO_JUMP_RUN_LEFT 131

#define ID_ANI_MARIO_SIT_RIGHT 104
#define ID_ANI_MARIO_SIT_LEFT 124

#define ID_ANI_MARIO_STOP_RIGHT 105
#define ID_ANI_MARIO_STOP_LEFT 125

#define ID_ANI_MARIO_KICK_RIGHT 107
#define ID_ANI_MARIO_KICK_LEFT 127

#define ID_ANI_MARIO_IDLE_HOLD_SHELL_RIGHT 108
#define ID_ANI_MARIO_IDLE_HOLD_SHELL_LEFT 128

#define ID_ANI_MARIO_WALK_HOLD_SHELL_RIGHT 109
#define ID_ANI_MARIO_WALK_HOLD_SHELL_LEFT 129

#define ID_ANI_MARIO_JUMP_HOLD_SHELL_RIGHT 110
#define ID_ANI_MARIO_JUMP_HOLD_SHELL_LEFT 130

#define ID_ANI_MARIO_DIE 599

// SMALL
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 140
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 160

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 141
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 161

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 142
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 162

#define ID_ANI_MARIO_SMALL_STOP_RIGHT 144
#define ID_ANI_MARIO_SMALL_STOP_LEFT 164

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 143
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 163

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 149
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 169

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 145
#define ID_ANI_MARIO_SMALL_KICK_LEFT 165

#define ID_ANI_MARIO_SMALL_IDLE_HOLD_SHELL_RIGHT 146
#define ID_ANI_MARIO_SMALL_IDLE_HOLD_SHELL_LEFT 166

#define ID_ANI_MARIO_SMALL_WALK_HOLD_SHELL_RIGHT 147
#define ID_ANI_MARIO_SMALL_WALK_HOLD_SHELL_LEFT 167

#define ID_ANI_MARIO_SMALL_JUMP_HOLD_SHELL_RIGHT 148
#define ID_ANI_MARIO_SMALL_JUMP_HOLD_SHELL_LEFT 168

// RACCOON
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 200
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 220

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 201
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 221

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 202
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 222

#define ID_ANI_MARIO_RACCOON_FALLING_RIGHT 207
#define ID_ANI_MARIO_RACCOON_FALLING_LEFT 227

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 203
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 223

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 206
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 226

#define ID_ANI_MARIO_RACCOON_STOP_RIGHT 204
#define ID_ANI_MARIO_RACCOON_STOP_LEFT 224

#define ID_ANI_MARIO_RACCOON_KICK_RIGHT 212
#define ID_ANI_MARIO_RACCOON_KICK_LEFT 232

#define ID_ANI_MARIO_RACCOON_IDLE_HOLD_SHELL_RIGHT 213
#define ID_ANI_MARIO_RACCOON_IDLE_HOLD_SHELL_LEFT 233

#define ID_ANI_MARIO_RACCOON_WALK_HOLD_SHELL_RIGHT 214
#define ID_ANI_MARIO_RACCOON_WALK_HOLD_SHELL_LEFT 234

#define ID_ANI_MARIO_RACCOON_FLY_HOLD_SHELL_RIGHT 215
#define ID_ANI_MARIO_RACCOON_FLY_HOLD_SHELL_LEFT 235

#define ID_ANI_MARIO_RACCOON_FLYING_UP_RIGHT 209
#define ID_ANI_MARIO_RACCOON_FLYING_UP_LEFT 230

#define ID_ANI_MARIO_RACCOON_FLYING_DOWN_RIGHT 210
#define ID_ANI_MARIO_RACCOON_FLYING_DOWN_LEFT 229

#define ID_ANI_MARIO_RACCOON_JUMP_WAG_TAIL_RIGHT 208
#define ID_ANI_MARIO_RACCOON_JUMP_WAG_TAIL_LEFT 228

#define ID_ANI_MARIO_RACCOON_FLY_WAG_TAIL_RIGHT 211
#define ID_ANI_MARIO_RACCOON_FLY_WAG_TAIL_LEFT 231

#define ID_ANI_MARIO_RACCOON_SPIN_TAIL_RIGHT 205
#define ID_ANI_MARIO_RACCOON_SPIN_TAIL_LEFT 225

#define ID_ANI_MARIO_RACCOON_GO_PIPE 240

// FIRE
#define ID_ANI_MARIO_FIRE_IDLE_RIGHT 300
#define ID_ANI_MARIO_FIRE_IDLE_LEFT 320
					
#define ID_ANI_MARIO_FIRE_WALKING_RIGHT 301
#define ID_ANI_MARIO_FIRE_WALKING_LEFT 321
					
#define ID_ANI_MARIO_FIRE_RUNNING_RIGHT 302
#define ID_ANI_MARIO_FIRE_RUNNING_LEFT 322

#define ID_ANI_MARIO_FIRE_FALLING_RIGHT 308
#define ID_ANI_MARIO_FIRE_FALLING_LEFT 328
					
#define ID_ANI_MARIO_FIRE_JUMP_WALK_RIGHT 303
#define ID_ANI_MARIO_FIRE_JUMP_WALK_LEFT 323
					
#define ID_ANI_MARIO_FIRE_JUMP_RUN_RIGHT 313
#define ID_ANI_MARIO_FIRE_JUMP_RUN_LEFT 333
					
#define ID_ANI_MARIO_FIRE_SIT_RIGHT 307
#define ID_ANI_MARIO_FIRE_SIT_LEFT 327
					
#define ID_ANI_MARIO_FIRE_STOP_RIGHT 304
#define ID_ANI_MARIO_FIRE_STOP_LEFT 324

#define ID_ANI_MARIO_FIRE_KICK_RIGHT 309
#define ID_ANI_MARIO_FIRE_KICK_LEFT 329
					
#define ID_ANI_MARIO_FIRE_IDLE_HOLD_SHELL_RIGHT 310
#define ID_ANI_MARIO_FIRE_IDLE_HOLD_SHELL_LEFT 330
					
#define ID_ANI_MARIO_FIRE_WALK_HOLD_SHELL_RIGHT 311
#define ID_ANI_MARIO_FIRE_WALK_HOLD_SHELL_LEFT 331
					
#define ID_ANI_MARIO_FIRE_JUMP_HOLD_SHELL_RIGHT 312
#define ID_ANI_MARIO_FIRE_JUMP_HOLD_SHELL_LEFT 332

#define ID_ANI_MARIO_FIRE_SHOOT_RIGHT 305
#define ID_ANI_MARIO_FIRE_SHOOT_LEFT 325

#define ID_ANI_MARIO_FIRE_SHOOT_JUMP_RIGHT 306
#define ID_ANI_MARIO_FIRE_SHOOT_JUMP_LEFT 326

#pragma endregion

#pragma region MARIO_LEVEL

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON	3
#define	MARIO_LEVEL_FIRE	4

#pragma endregion

#pragma region MARIO_BBOX_SIZE

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_BIG_IDLE_OFFSET_LEFT_L 2
#define MARIO_BIG_IDLE_OFFSET_TOP	13
#define MARIO_BIG_SITTING_OFFSET_TOP 4

#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 18

#define MARIO_RACCOON_IDLE_OFFSET_LEFT_L 2
#define MARIO_RACCOON_IDLE_OFFSET_TOP 14
#define MARIO_RACCOON_BBOX_WIDTH 14
#define MARIO_RACCOON_BBOX_HEIGHT 28

#define MARIO_SMALL_IDLE_OFFSET_LEFT 1
#define MARIO_SMALL_IDLE_OFFSET_TOP 2

#define MARIO_SMALL_BBOX_WIDTH  14
#define MARIO_SMALL_BBOX_HEIGHT 16

#pragma endregion

#define MARIO_SPEED_ON_MAP	0.1f

#define MARIO_ON_OVERWORLD_MAP_ANI_SMALL	1
#define MARIO_ON_OVERWORLD_MAP_ANI_BIG		2
#define MARIO_ON_OVERWORLD_MAP_ANI_RACCOON	3
#define MARIO_ON_OVERWORLD_MAP_ANI_FIRE		4

#define ALLOWED_TO_GO_LEFT	0
#define ALLOWED_TO_GO_RIGHT	1
#define ALLOWED_TO_GO_UP	2
#define ALLOWED_TO_GO_DOWN	3

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICK_SHELL_TIME 200
#define MARIO_SPIN_TAIL_TIME 250
#define MARIO_WAG_TAIL_TIME 450

#define START_POINT_X	40
#define START_POINT_Y	64

class CMario : public CGameObject
{
	static CMario* __instance;

	CTimer* spinTail = new CTimer(MARIO_SPIN_TAIL_TIME);
	CTimer* wagTail = new CTimer(MARIO_WAG_TAIL_TIME);
	CTimer* powerMode = new CTimer(6000);
	//CTimer* powerMode = new CTimer(1000000);

	CTail* tail = new CTail(spinTail);

	BOOLEAN isSitting;

	float maxVx;
	float dax;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	

	int untouchable; 
	ULONGLONG untouchable_start;

	int coin; 

	/*BOOLEAN isOnPlatform;*/

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithPandoraBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranha();

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();
	int GetAniIdFire();

public:
	CTimer* kickShell = new CTimer(MARIO_KICK_SHELL_TIME);
	BOOLEAN isHoldingShell;
	BOOLEAN isInPipe;
	CMapPoint* currentPoint = new CMapPoint(START_POINT_X, START_POINT_Y, Type::MAP_POINT, 4, 0, 1, 0, 0, 1);
	vector<bool> movementPermission{ 0, 1, 0, 0 };
	BOOLEAN isOnPlatform;
	int isOnWorldMap;
	int atHiddenPortal;

	CMario(float x, float y, Type type) : CGameObject(x, y, type)
	{
		isOnWorldMap = 0;
		powerMode->Start();
		atHiddenPortal = 0;
		isHoldingShell = false;
		isSitting = false;
		isInPipe = false;
		isOnPlatform = false;
		maxVx = 0.0f;
		dax = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void UpdateOnWorldMap(DWORD dt, vector<LPGAMEOBJECT>* coPoints);
	void Render();
	void RenderOnWorldMap();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int GetLevel() { return this->level; }

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	BOOLEAN IsOnPowerMode() { return !(powerMode->IsTimeUp() || powerMode->IsStopped()); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetCollisionWithHiddenPortal(int portalType) { atHiddenPortal = portalType; }
	int GetCollisionWithHiddenPortal() { return atHiddenPortal; }

	void DecelerateSlightly();

	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	int GetUntouchable() { return untouchable; }

	void HitByEnemy();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	float GetSpeedX() { return this->vx; }
	float GetSpeedY() { return this->vy; }
	float GetPosY() { return this->y; }
	void SetSpeedY(float vy) { this->vy = vy; }

	static CMario* GetInstance();
};