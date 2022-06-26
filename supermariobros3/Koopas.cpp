#include "Koopas.h"
#include "Collision.h"
#include "Platform.h"
#include "debug.h"
#include "PlayScene.h"
#include "PiranhaPlant.h"
#include "PiranhaPlantFire.h"
#include "Goomba.h"

CKoopas::CKoopas(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GLOBAL_GRAVITY;
	die_start = -1;
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if ((state == KOOPAS_STATE_STOMPED) || (state == KOOPAS_STATE_ROLLING))
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
	x += vx * dt;
	y += vy * dt;

}

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);

	if (dynamic_cast<CPlatform*>(e->obj))
	{
		OnCollisionWithPlatform(e);
	}

	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);

	if (dynamic_cast<PiranhaPlant*>(e->obj) || dynamic_cast<PiranhaPlantFire*>(e->obj))
		OnCollisionWithPlan(e);

	if (!e->obj->IsBlocking()) return;

	if (dynamic_cast<CKoopas*>(e->obj)) return;



	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::OnCollisionWithPlan(LPCOLLISIONEVENT e) {

	PiranhaPlant* piranhaPlant = dynamic_cast<PiranhaPlant*>(e->obj);
	PiranhaPlantFire* piranhaPlantFire = dynamic_cast<PiranhaPlantFire*>(e->obj);

	if ((piranhaPlant->GetState() != PIRANHAPLANT_STATE_DEATH ||
		piranhaPlantFire->GetState() != PIRANHAPLANT_STATE_DEATH) &&
		this->GetState() == KOOPAS_STATE_ROLLING);
	{
		piranhaPlant->SetState(PIRANHAPLANT_STATE_DEATH);
		piranhaPlantFire->SetState(PIRANHAPLANT_STATE_DEATH);
	}
}

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* b = (CBrick*)e->obj;
	if (e->nx != 0 && this->state == KOOPAS_STATE_ROLLING) {
		if (b->Type() == BRICK_BREAKABLE) {
			b->Break();
		}
		else
			b->Hit();
	}
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = (CGoomba*)e->obj;
	if (e->nx != 0 && this->state == KOOPAS_STATE_ROLLING) {
		goomba->Downgrade();
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
		if (xx >= p->GetEnd() - KOOPAS_BBOX_WIDTH)
		{
			vx = -KOOPAS_WALKING_SPEED;
		}
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	vy += ay * dt;
	vx += ax * dt;

	//if ((state == KOOPAS_STATE_STOMPED) && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}

	HandleBeingHeld(mario);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::HandleBeingHeld(LPGAMEOBJECT player) {

	CMario* mario = dynamic_cast<CMario*>(player);
	int mNx = mario->GetDirection();
	float mx, my;
	mario->GetPosition(mx, my);

	if (isBeingHeld && mario->isHolding) {
		if (state == KOOPAS_STATE_STOMPED) {
			if (mNx > 0) {
				x = mx + MARIO_BIG_BBOX_WIDTH * mNx - 3.0f;
			}
			else x = mx + MARIO_BIG_BBOX_WIDTH * mNx;
			if (mario->GetLevel() != MARIO_LEVEL_SMALL) {
				y = my - 2.0f;
			}
			else {
				y = my - 2.0f;
			}
			vy = 0;
		}
	}
	else if (isBeingHeld && !mario->isHolding) {
		if (state == KOOPAS_STATE_STOMPED) {
			this->nx = mario->GetDirection();
			isBeingHeld = false;
			mario->StartKicking();
			SetState(KOOPAS_STATE_ROLLING);
		}
	}
}

void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING;


	if (state == KOOPAS_STATE_STOMPED || state == KOOPAS_STATE_ROLLING)
	{
		aniId = ID_ANI_KOOPAS_DIE;
	}

	if (vx >= 0) nx = -1;
	else if (vx < 0) nx = 1;
	CAnimations::GetInstance()->Get(aniId)->Render(nx, x, y);
	RenderBoundingBox();
}


void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_STOMPED:
		if (isDieByTail) {
			DieByTail();
			ay = GLOBAL_GRAVITY;
		}
		vx = 0;
		break;
	case KOOPAS_STATE_ROLLING:
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		vx = KOOPAS_ROLLING_SPEED * mario->GetDirectionX();
		break;
	}
}

void CKoopas::Downgrade()
{
	if (state == KOOPAS_STATE_WALKING)
		SetState(KOOPAS_STATE_STOMPED);
	else if (state == KOOPAS_STATE_STOMPED)
		SetState(KOOPAS_STATE_ROLLING);
	else if (state == KOOPAS_STATE_ROLLING)
		SetState(KOOPAS_STATE_STOMPED);
}