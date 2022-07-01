#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>

#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
#include "Collision.h"
#include "AssetIDs.h"

using namespace std;

#define GLOBAL_GRAVITY 0.0025f
#define BBOX_ALPHA 0.25f
#define DEFLECT_VY 0.3f

class CGameObject
{
protected:

	float x;
	float y;

	float vx;
	float vy;
	int tag = 0;

	int nx;

	int state;

	bool isDeleted;

	// For enemy only
	bool isDieByTail = false;
	int isBlocking = 1;
public:
	bool IsDieByTail() { return isDieByTail; }
	void SetIsDieByTail(bool die) { isDieByTail = die; }

	void SetTag(int tag) { this->tag = tag; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	int GetX() { return this->x; }
	int GetY() { return this->y; }
	int GetTag() { return this->tag; }
	int GetState() { return this->state; }
	int GetDirectionX() { return this->nx; }
	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }
	int GetDirection() { return this->nx; }
	void SetDirection(int nx) { this->nx = nx; }

	void DieByTail() {
		vx = -vx;
		vy = -DEFLECT_VY;
	}

	void RenderBoundingBox();

	CGameObject();
	CGameObject(float x, float y) :CGameObject() { this->x = x; this->y = y; }


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void Downgrade() {};

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return isBlocking; }
	void SetIsBlocking(bool block) { this->isBlocking = block; }

	virtual int IsSpecialPlatform() { return 0; }

	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT& o) { return o->isDeleted; }
};
