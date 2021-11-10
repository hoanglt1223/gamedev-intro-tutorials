#include "Koopas.h"
#include "Collision.h"
#include "Platform.h"
#include "debug.h"

CKoopas::CKoopas(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GLOBAL_GRAVITY;
	die_start = -1;
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if ((state == KOOPAS_STATE_DIE) || (state == KOOPAS_STATE_HIT))
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
	}
	else if (state == KOOPAS_STATE_WALKING)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	if (state == KOOPAS_STATE_DIE)
	{
		x += vx * dt;
		y += vy * dt;
	}
	else if (state == KOOPAS_STATE_HIT)
	{
		x += vx * dt;
		y += vy * dt;
	}
	else if (state == KOOPAS_STATE_WALKING) {
		x += vx * dt;
		y += vy * dt;
	}
}

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	if (dynamic_cast<CPlatform*>(e->obj))
	{
		OnCollisionWithPlatform(e);
	}

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* p = dynamic_cast<CPlatform*>(e->obj);
		float xx = x;
		if (state == KOOPAS_STATE_WALKING)
		{
			if (xx <= p->GetStart())
			{
				vx = KOOPAS_WALKING_SPEED;
			}
			if (xx >= p->GetEnd())
			{
				vx = -KOOPAS_WALKING_SPEED;
			}
		}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPAS_STATE_HIT) && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING;

	if (vx < 0) {
		aniId = ID_ANI_KOOPAS_WALKING;
	}
	else if (vx > 0) {
		aniId = ID_ANI_KOOPAS_WALKING;
	}
	if (state == KOOPAS_STATE_DIE)
	{
		aniId = ID_ANI_KOOPAS_DIE;
	}
	else if (state == KOOPAS_STATE_HIT)
	{
		aniId = ID_ANI_KOOPAS_HIT;
	}

	if (vx >= 0) nx = -1;
	else if (vx < 0) nx = 1;
	CAnimations::GetInstance()->Get(aniId)->Render(nx, x, y);
	//RenderBoundingBox();
}


void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		y -= 10;
		vx = 0;
		vy = 0;
		ax = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_HIT:
		vx = 0;
		vy = 0;
		break;
	}
}