#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_BREAKABLE 10000
#define ID_ANI_BRICK_QUESTION_MARK 10001
#define ID_ANI_BRICK_QUESTION_EMPTY 10002

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_COIN 1
#define BRICK_1UP 2
#define BRICK_STARMAN 3
#define BRICK_POWER_UP 4
#define BRICK_BREAKABLE 5
#define BRICK_PSWITCH 6

#define BRICK_STATE_DEFAULT 0 
#define BRICK_STATE_EMPTY 1


#define TYPE
class CBrick : public CGameObject {
	int type;
	bool isHit;

	float imitateY{}, entryY{};
	ULONGLONG timer;
public:
	CBrick(float x, float y, int type);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Break();
	void Hit();
	int Type() { return type; }
};