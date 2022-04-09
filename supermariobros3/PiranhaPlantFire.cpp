#include "PiranhaPlantFire.h"
#include "FireBullet.h"
#include "PlayScene.h"

PiranhaPlantFire::PiranhaPlantFire()
{
}

PiranhaPlantFire::PiranhaPlantFire(float x, float y, int tag) :CGameObject(x, y) {

	this->tag = tag;
	SetState(PIRANHAPLANT_STATE_INACTIVE);
}

void PiranhaPlantFire::Render()
{
	int aniId = PIRANHAPLANT_ANI_DEATH;
	if (state != PIRANHAPLANT_STATE_DEATH && dying_start == 0)
	{
		if (tag == 1)
		{
			if (Up)
				if (Right)
					aniId = PIRANHAPLANT_ANI_RED_RIGHT_UP;
				else
					aniId = PIRANHAPLANT_ANI_RED_LEFT_UP;
			else
				if (Right)
					aniId = PIRANHAPLANT_ANI_RED_RIGHT_DOWN;
				else
					aniId = PIRANHAPLANT_ANI_RED_LEFT_DOWN;
		}
		else {
			if (Up)
				if (Right)
					aniId = PIRANHAPLANT_ANI_GREEN_RIGHT_UP;
				else
					aniId = PIRANHAPLANT_ANI_GREEN_LEFT_UP;
			else
				if (Right)
					aniId = PIRANHAPLANT_ANI_GREEN_RIGHT_DOWN;
				else
					aniId = PIRANHAPLANT_ANI_GREEN_LEFT_DOWN;
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(nx, x, y);
	RenderBoundingBox();
}

void PiranhaPlantFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (GetTickCount64() - dying_start >= PIRANHAPLANT_DIYING_TIME && dying_start != 0)
		isDeleted = true;

	if (state == PIRANHAPLANT_STATE_DEATH)
		return;

	CGameObject::Update(dt);
	y += vy * dt;

	GetDirect();

	if (y <= limitY && vy < 0)
	{
		y = limitY;
		vy = 0;
		StartAim();
	}

	if (y >= limitY + BBHeight && vy > 0)
	{
		y = limitY + BBHeight + 12;
		SetState(PIRANHAPLANT_STATE_INACTIVE);
		StartDelay();
	}

	if (GetTickCount64() - aim_start >= PIRANHAPLANT_AIM_TIME && aim_start != 0)
	{
		aim_start = 0;
		SetState(PIRANHAPLANT_STATE_SHOOTING);
		StartDelay();
	}

	if (GetTickCount64() - delay_start >= PIRANHAPLANT_DELAY_TIME && delay_start != 0)
	{
		delay_start = 0;
		if (y == limitY)
			vy = PIRANHAPLANT_DARTING_SPEED;
	}

}


void PiranhaPlantFire::GetBoundingBox(float& left, float& top,
	float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PIRANHAPLANT_BBOX_WIDTH;
	bottom = y + BBHeight;
}

void PiranhaPlantFire::SetState(int state) {
	CGameObject::Update(state);
	switch (state)
	{
	case PIRANHAPLANT_STATE_DARTING:
		vy = -PIRANHAPLANT_DARTING_SPEED;
		break;
	case PIRANHAPLANT_STATE_SHOOTING:
		vy = 0;
		Shoot();
		break;
	case PIRANHAPLANT_STATE_DEATH:
		vy = 0;
		//SetType(IGNORE);
		StartDying();
		break;
	case PIRANHAPLANT_STATE_INACTIVE:
		vy = 0;
		break;
	}
}

void PiranhaPlantFire::GetDirect() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	int mHeight;
	float x, y;
	mario->GetXandY(x, y);
	if (mario->GetLevel() == MARIO_LEVEL_SMALL)
		mHeight = MARIO_SMALL_BBOX_HEIGHT;
	else
		mHeight = MARIO_BIG_BBOX_HEIGHT;

	if (y + mHeight < limitY + BBHeight)
		Up = true;
	else
		Up = false;
	if (x <= x)
		Right = false;
	else
		Right = true;
};

void PiranhaPlantFire::Shoot() {

}