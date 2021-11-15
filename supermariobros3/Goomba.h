#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.03f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 5

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_DIE 0
#define GOOMBA_STATE_WALKING 1
#define GOOMBA_STATE_JUMPING 2

#define GOOMBA_TYPE_BROWN 0
#define GOOMBA_TYPE_RED 1

#define ID_ANI_GOOMBA_DIE 5000
#define ID_ANI_GOOMBA_WALKING 5001
#define ID_ANI_GOOMBA_SKIPPING 5002
#define ID_ANI_GOOMBA_JUMPING 5003

#define GOOMBA_ANI_ID_OFFSET 10

#define GOOMBA_JUMP_INTERVAL 2000
#define GOOMBA_JUMP_DELAY 3500

#define GOOMBA_SKIP_VY 0.08f
#define GOOMBA_JUMP_VY 0.25f


class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay;
	int type;

	ULONGLONG die_start;
	ULONGLONG timer;
	int skippingCounter;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void Jump();

public: 	
	CGoomba(float x, float y, int initialState, int type);
	virtual void SetState(int state);
	virtual void Downgrade();
};