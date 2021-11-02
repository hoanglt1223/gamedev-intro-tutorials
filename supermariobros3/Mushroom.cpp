#include "Mushroom.h"
#include "Game.h"
#include "PlayScene.h"
#include "Mario.h"
#include "Goomba.h"
#include "Brick.h"

CMushroom::CMushroom(float x, float y, int type) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GLOBAL_GRAVITY;
	this->x = x;
	this->y = y;
	entryX = x;
	entryY = y;
	this->type = type;

	growingDelay = 0;
	SetState(MUSHROOM_STATE_MOVING);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Render()
{
	CAnimations::GetInstance()->Get(7000)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MUSHROOM_STATE_MOVING:
		vx = nx * MUSHROOM_MOVING_SPEED;
		break;
	}
}