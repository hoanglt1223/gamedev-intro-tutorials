#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_FLYING_SPEED		0.1f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f
#define MARIO_ACCEL_FLY_X	0.0008f

#define MARIO_LIMIX_X		10
#define PLUS_X_VALUE		2

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_BIG_JUMP_SPEED_Y		0.6f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_INTO_PIPE		800

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_AIRBORNE		700
#define MARIO_STATE_AIRBORNE_LEFT	701
#define MARIO_STATE_AIRBORNE_RIGHT	702

#define MARIO_STATE_KICK			703
#define MARIO_STATE_TAIL_ATTACK		704


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_SMALL_IDLE 400
#define ID_ANI_MARIO_BIG_IDLE 401
#define ID_ANI_MARIO_RACOON_IDLE 402

#define ID_ANI_MARIO_SMALL_WALKING 404
#define ID_ANI_MARIO_BIG_WALKING 405
#define ID_ANI_MARIO_RACOON_WALKING 406

#define ID_ANI_MARIO_SMALL_JUMP_WALK 408
#define ID_ANI_MARIO_BIG_JUMP 409
#define ID_ANI_MARIO_RACOON_JUMP 410

#define ID_ANI_MARIO_SMALL_RUNNING 412
#define ID_ANI_MARIO_BIG_RUNNING 413
#define ID_ANI_MARIO_RACOON_RUNNING 414

#define ID_ANI_MARIO_SMALL_BRACE 424
#define ID_ANI_MARIO_BIG_BRACE 425
#define ID_ANI_MARIO_RACOON_BRACE 426

#define ID_ANI_MARIO_SMALL_JUMP_RUN 408
#define ID_ANI_MARIO_BIG_JUMP_RUN 460
#define ID_ANI_MARIO_RACOON_JUMP_RUN 461

#define ID_ANI_MARIO_BIG_SIT 440
#define ID_ANI_MARIO_RACOON_SIT 441

#define ID_ANI_MARIO_RACOON_AIRBORNE 445
#define ID_ANI_MARIO_RACOON_FLYING 446

#define ID_ANI_MARIO_BIG_JUMPED 460
#define ID_ANI_MARIO_RACOON_JUMPED 461

#define ID_ANI_MARIO_SMALL_HOLD_IDLE 432
#define ID_ANI_MARIO_BIG_HOLD_IDLE 433
#define ID_ANI_MARIO_RACOON_HOLD_IDLE 435

#define ID_ANI_MARIO_SMALL_HOLD_RUN 436
#define ID_ANI_MARIO_BIG_HOLD_RUN 437
#define ID_ANI_MARIO_RACOON_HOLD_RUN 439

#define ID_ANI_MARIO_SMALL_HOLD_JUMP 452
#define ID_ANI_MARIO_BIG_HOLD_JUMP 453
#define ID_ANI_MARIO_RACOON_HOLD_JUMP 455

#define ID_ANI_MARIO_SMALL_KICK 428
#define ID_ANI_MARIO_BIG_KICK 429
#define ID_ANI_MARIO_RACOON_KICK 431

#define ID_ANI_MARIO_RACOON_TAIL_ATTACK 444

#define ID_ANI_MARIO_DIE 499

#define ID_ANI_MARIO_SMALL_PIPE 456
#define ID_ANI_MARIO_BIG_PIPE 457

#pragma endregion


#define GROUND_Y 160.0f


#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  16
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICKING_TIME	200	
#define MARIO_TURNING_STATE_TIME	60
#define MARIO_TURNING_TAIL_TIME		300

#define MAX_POWER_METER 7


#define EXTRA_SCENE_STARTX 2980
#define EXTRA_SCENE_STARTY 200

#define OUT_OF_EXTRA_SCENE_STARTX 2320
#define OUT_OF_EXTRA_SCENE_STARTY 300


class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isAirborne;
	BOOLEAN isFlying;
	float maxVx;
	float ax, ay;				// acceleration on x, y
	//float lastVx, lastVy;

	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin;
	int powerMeter;
	ULONGLONG powerTimer;
	ULONGLONG flyTimer;
	ULONGLONG start_kicking = 0;
	ULONGLONG start_turning_state = 0;
	ULONGLONG start_turning = 0;


	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithSwitch(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

	void HandleMarioKicking();
	void HandleTurning();

public:
	BOOLEAN isHolding = false;
	BOOLEAN isReadyToHold = false;
	BOOLEAN isKick = false;
	BOOLEAN isFinish = false;
	BOOLEAN isInExtraScene = false;
	// TAIL_ATTACK
	BOOLEAN isTuring = false;
	int turningStack = 0;

	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isAirborne = false;
		isFlying = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		//level = MARIO_LEVEL_SMALL;
		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		powerMeter = 0;
		powerTimer = 0;
		flyTimer = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);

	virtual int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	virtual int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetLevel(int l);
	int GetLevel() {
		return this->level;
	}

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartKicking() { start_kicking = GetTickCount64(); isKick = true; }
	void StopKicking() { start_kicking = 0; isKick = false; }
	void StartTurning() { start_turning_state = GetTickCount64(); isTuring = true; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Downgrade();

	void GetXandY(float& x, float& y) {
		x = this->x;
		y = this->y;
	}

	void AddCoin() { coin++; }
	void Respawn();
	void Flying() { isFlying = true; }

	bool IsPowerMaxed() { return powerMeter == MAX_POWER_METER ? true : false; }

	bool IsSitting() { return isSitting; }
	bool IsOnPlatform() { return isOnPlatform; }
	bool IsAirBorne() { return isAirborne; }
	void TelePort(float x,float y) {
		this->x = x;
		this->y = y;
	}
};