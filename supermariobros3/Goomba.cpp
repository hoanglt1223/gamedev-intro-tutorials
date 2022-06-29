#include "Goomba.h"
#include "PlayScene.h"
#include "Platform.h"

CGoomba::CGoomba(float x, float y, int initialState, int type) :CGameObject(x, y)
{
	this->ax = 0;
	die_start = -1;
	this->type = type;
	SetState(initialState);
	timer = 0;
	skippingCounter = 0;
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
		if (state == GOOMBA_STATE_JUMPING) Jump();
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

}


void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if (state == GOOMBA_STATE_JUMPING) timer += dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
		aniId = ID_ANI_GOOMBA_DIE;
	else if (state == GOOMBA_STATE_JUMPING) {
		if (vy >= 0) aniId = ID_ANI_GOOMBA_SKIPPING;
		else aniId = ID_ANI_GOOMBA_JUMPING;
	}

	if (type == GOOMBA_TYPE_RED) aniId += GOOMBA_ANI_ID_OFFSET;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		if (isDieByTail) {
			DieByTail();
			ay = GLOBAL_GRAVITY;
		}
		else
		{
			vx = 0;
			ay = 0;
			vy = 0;
		}
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		ay = GLOBAL_GRAVITY;
		break;
	case GOOMBA_STATE_JUMPING:
		vx = -GOOMBA_WALKING_SPEED;
		ay = GLOBAL_GRAVITY / 5;
		break;
	}
}

void CGoomba::Jump()
{
	if (timer < GOOMBA_JUMP_INTERVAL)
	{
		if (skippingCounter < 3)
		{
			skippingCounter++;
			vy -= GOOMBA_SKIP_VY;
		}
		else if (skippingCounter == 3) {
			skippingCounter++;
			vy -= GOOMBA_JUMP_VY;
		}
	}
	if (timer > GOOMBA_JUMP_DELAY)
	{
		timer = 0;
		skippingCounter = 0;
		float marioX, marioY;
		LPSCENE scene = CGame::GetInstance()->GetCurrentScene();
		((LPPLAYSCENE)scene)->GetPlayer()->GetPosition(marioX, marioY);

		if ((marioX > x && vx < 0) || (marioX < x && vx > 0)) vx = -vx;
	}
}

void CGoomba::Downgrade()
{
	if (state == GOOMBA_STATE_JUMPING) SetState(GOOMBA_STATE_WALKING);
	else if (state == GOOMBA_STATE_WALKING) SetState(GOOMBA_STATE_DIE);
}
