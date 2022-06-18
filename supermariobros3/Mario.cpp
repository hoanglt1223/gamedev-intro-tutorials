#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Koopas.h"
#include "Brick.h"
#include "Mushroom.h"
#include "PiranhaPlant.h"
#include "PiranhaPlantFire.h"
#include "Platform.h"
#include "Collision.h"
#include "PlayScene.h"
#include "Leaf.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;


	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if (state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_RUNNING_RIGHT) {
		powerMeter = (int)floor(abs(vx) / abs(maxVx) * MAX_POWER_METER);
		if (abs(vx) > abs(maxVx)) powerMeter = MAX_POWER_METER;
		powerTimer = 0;
	}
	else if (powerMeter > 0) {
		powerTimer += dt;
		if (powerTimer > 200) {
			powerTimer -= 200;
			powerMeter--;
		}
	}
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHUD()->SetPowerMeter(powerMeter);



	if (isAirborne)
	{
		vy /= 1.5f;
	}

	if (isFlying) {
		if (flyTimer > 3000) isFlying = false;
		flyTimer += dt;
		vy = -0.125f;
	}
	else {
		flyTimer = 0;
		ay = MARIO_GRAVITY;
	}


	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (isOnPlatform) {
		isAirborne = false;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0 && e->obj->IsBlocking()) vx = 0;

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<PiranhaPlant*> (e->obj) || dynamic_cast<PiranhaPlantFire*> (e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<FireBullet*>(e->obj))
		OnCollisionWithFireBullet(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->Downgrade();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
			Downgrade();
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e) {
	e->obj->Delete();
	this->SetLevel(MARIO_LEVEL_RACOON);
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	if (koopas->GetState() != KOOPAS_STATE_STOMPED) {
		if (e->ny < 0)
		{
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			koopas->Downgrade();
			koopas->SetDirection(this->nx);
		}
		else Downgrade();
	}

	else
	{
		koopas->Downgrade();
		koopas->SetDirection(this->nx);
	}
}


void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* b = (CBrick*)e->obj;
	if (e->ny > 0) {
		b->Hit();
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	SetLevel(MARIO_LEVEL_BIG);
	CMushroom* m = (CMushroom*)e->obj;
	m->Delete();
}

void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	Downgrade();
}

void CMario::OnCollisionWithFireBullet(LPCOLLISIONEVENT e) {
	e->obj->Delete();
	Downgrade();
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_SMALL_JUMP_RUN;
		else aniId = ID_ANI_MARIO_SMALL_JUMP_WALK;
	}
	else
		if (isSitting)
			aniId = ID_ANI_MARIO_BIG_SIT;
		else if (vx == 0) aniId = ID_ANI_MARIO_SMALL_IDLE;
		else if (ax * vx < 0) aniId = ID_ANI_MARIO_SMALL_BRACE;
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_SMALL_RUNNING;
		else if (abs(ax) == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_SMALL_WALKING;

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE;

	return aniId;
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_BIG_JUMP_RUN;
		else if (vy < 0) aniId = ID_ANI_MARIO_BIG_JUMP;
		else aniId = ID_ANI_MARIO_BIG_JUMPED;
	}
	else
		if (isSitting) aniId = ID_ANI_MARIO_BIG_SIT;
		else if (vx == 0) aniId = ID_ANI_MARIO_BIG_IDLE;
		else if (ax * vx < 0) aniId = ID_ANI_MARIO_BIG_BRACE;
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_BIG_RUNNING;
		else if (abs(ax) == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_BIG_WALKING;

	if (aniId == -1) aniId = ID_ANI_MARIO_BIG_IDLE;

	return aniId;
}

//
// Get animdation ID for Racoon Mario
//
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X) aniId = ID_ANI_MARIO_RACOON_JUMP_RUN;
		else if (vy < 0) aniId = ID_ANI_MARIO_RACOON_JUMP;
		else aniId = ID_ANI_MARIO_RACOON_JUMPED;
		if (isFlying)
			aniId = ID_ANI_MARIO_RACOON_FLYING;
	}
	else
		if (isSitting) aniId = ID_ANI_MARIO_RACOON_SIT;
		else if (vx == 0) aniId = ID_ANI_MARIO_RACOON_IDLE;
		else if (ax * vx < 0) aniId = ID_ANI_MARIO_RACOON_BRACE;
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_RACOON_RUNNING;
		else if (abs(ax) == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_RACOON_WALKING;
		else if (isAirborne) aniId = ID_ANI_MARIO_RACOON_AIRBORNE;
		else if (isFlying) aniId = ID_ANI_MARIO_RACOON_FLYING;

	if (aniId == -1) aniId = ID_ANI_MARIO_RACOON_IDLE;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(-nx, x, y);


	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE || CGame::GetInstance()->IsPaused()) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else if (level == MARIO_LEVEL_SMALL) vy = -MARIO_JUMP_SPEED_Y;
			else vy = -MARIO_BIG_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_AIRBORNE:
		if (isOnPlatform) {
			SetState(MARIO_STATE_IDLE);
			break;
		}
		if (level == MARIO_LEVEL_RACOON)
			isAirborne = true;
		break;

	case MARIO_STATE_AIRBORNE_RIGHT:
		if (isSitting) break;
		if (level == MARIO_LEVEL_RACOON)
		{
			isAirborne = true;
			if (isOnPlatform && IsPowerMaxed()) 
			{
				isFlying = true;
				isOnPlatform = false;
			}

		}
		if (isOnPlatform)
			SetState(MARIO_STATE_JUMP);
		maxVx = MARIO_FLYING_SPEED;
		ax = MARIO_ACCEL_FLY_X;
		nx = 1;
		break;

	case MARIO_STATE_AIRBORNE_LEFT:
		if (isSitting) break;
		if (level == MARIO_LEVEL_RACOON)
		{
			isAirborne = true;
			if (isOnPlatform && IsPowerMaxed())
			{
				isFlying = true;
				isOnPlatform = false;
			}
		}
		if (isOnPlatform)
			SetState(MARIO_STATE_JUMP);
		maxVx = -MARIO_FLYING_SPEED;
		ax = -MARIO_ACCEL_FLY_X;
		nx = -1;
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		isAirborne = false;
		isFlying = false;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	int diffLeft = 4;
	int diffRight = 8;
	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_RACOON)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			if (level == MARIO_LEVEL_RACOON)
			{
				left = x - MARIO_BIG_BBOX_WIDTH / 2 - diffLeft;
				top = y - MARIO_BIG_BBOX_HEIGHT / 2;
				right = left + MARIO_BIG_BBOX_WIDTH + diffRight;
				bottom = top + MARIO_BIG_BBOX_HEIGHT;
			}
			else
			{
				left = x - MARIO_BIG_BBOX_WIDTH / 2;
				top = y - MARIO_BIG_BBOX_HEIGHT / 2;
				right = left + MARIO_BIG_BBOX_WIDTH;
				bottom = top + MARIO_BIG_BBOX_HEIGHT;
			}
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::Downgrade()
{
	if (untouchable == 1) return;

	if (level > MARIO_LEVEL_SMALL)
	{
		level = MARIO_LEVEL_SMALL;
		vy = MARIO_GRAVITY;
		StartUntouchable();
	}
	else SetState(MARIO_STATE_DIE);
}

void CMario::Respawn()
{
	state = MARIO_STATE_IDLE;
	SetState(MARIO_STATE_IDLE);
	SetPosition(x < 20 ? 20 : x, 200);
}

