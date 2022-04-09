#pragma once
#include "PiranhaPlant.h"
#include "FireBullet.h"
#include "GameObject.h"


#define PIRANHAPLANT_GREEN_TYPE					0
#define PIRANHAPLANT_RED_TYPE					1

#define PIRANHAPLANT_BBOX_WIDTH					20
#define PIRANHAPLANT_GREEN_BBOX_HEIGHT			24
#define PIRANHAPLANT_RED_BBOX_HEIGHT			32
#define PIRANHAPLANT_DARTING_SPEED				0.03f
#define PIRANHAPLANT_BBOX_DEATH_WIDTH			16
#define PIRANHAPLANT_BBOX_DEATH_HEIGHT			24

#define PIRANHAPLANT_STATE_DARTING				0
#define PIRANHAPLANT_STATE_SHOOTING				100
#define PIRANHAPLANT_STATE_DEATH				200
#define PIRANHAPLANT_STATE_INACTIVE				300

#define PIRANHAPLANT_ANI_GREEN_RIGHT_UP			7200
#define PIRANHAPLANT_ANI_GREEN_RIGHT_DOWN		7201
#define PIRANHAPLANT_ANI_GREEN_LEFT_UP			7210
#define PIRANHAPLANT_ANI_GREEN_LEFT_DOWN		7211

#define PIRANHAPLANT_ANI_RED_RIGHT_UP		7100
#define PIRANHAPLANT_ANI_RED_RIGHT_DOWN		7101
#define PIRANHAPLANT_ANI_RED_LEFT_UP		7110
#define PIRANHAPLANT_ANI_RED_LEFT_DOWN		7111
//#define PIRANHAPLANT_ANI_DEATH				4

#define PIRANHAPLANT_DELAY_TIME			750
#define PIRANHAPLANT_AIM_TIME			750
#define PIRANHAPLANT_DIYING_TIME		250

#define PIRANHAPLANT_ACTIVE_RANGE		20

#define BULLET_ANI_SET_ID		9

class PiranhaPlantFire : public CGameObject

{
	ULONGLONG shooting_start = 0;
	ULONGLONG aim_start = 0;
	ULONGLONG delay_start = 0;
	ULONGLONG dying_start = 0;
	float limitY = 0;
	bool Up = false;
	bool Right = false;
	int BBHeight = 0;
	bool isMarioInActiveZone = false;
	int tag = 0;

	FireBullet* bullet = NULL;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>*colliable_objects = NULL);
	virtual void Render();
public:
	PiranhaPlantFire();
	PiranhaPlantFire(float x, float y, int tag);

	void GetDirect();
	void StartShooting() { shooting_start = GetTickCount64(); }
	void StartAim() { aim_start = GetTickCount64(); }
	void StartDelay() { delay_start = GetTickCount64(); }
	void StartDying() { dying_start = GetTickCount64(); }
	void Shoot();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	void SetLimitY(float ly)
	{
		if (tag == 0)
			BBHeight = PIRANHAPLANT_GREEN_BBOX_HEIGHT;
		else BBHeight = PIRANHAPLANT_RED_BBOX_HEIGHT;
		limitY = ly - BBHeight;
	}
};