#pragma once

#include "GameObject.h"

#define MUSHROOM_MOVING_SPEED 0.06f
#define MUSHROOM_GROWING_SPEED 0.03f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14
#define MUSHROOM_GROWING_HEIGHT 17

#define MUSHROOM_GROWING_DELAY 200

#define MUSHROOM_POWERUP 0

#define ID_ANI_MUSHROOM_POWERUP 7000

#define MUSHROOM_STATE_GROWING 0
#define MUSHROOM_STATE_MOVING 1

class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	int type;
	float entryX, entryY;
	ULONGLONG growingDelay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y, int type);
	virtual void SetState(int state);
};