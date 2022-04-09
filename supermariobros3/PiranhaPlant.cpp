#include "PiranhaPlant.h"
#include "Game.h"
#include "PlayScene.h"

void PiranhaPlant::GetBoundingBox(float& left, float& top,
	float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PIRANHAPLANT_BBOX_WIDTH;
	bottom = y + PIRANHAPLANT_BBOX_HEIGHT;
}

PiranhaPlant::PiranhaPlant(float x, float y) : CGameObject(x, y)
{
	//SetState(PIRANHAPLANT_STATE_INACTIVE);
	SetState(PIRANHAPLANT_STATE_DARTING);
}

PiranhaPlant::PiranhaPlant()
{
}

void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (GetTickCount64() - dying_start >= PIRANHAPLANT_DIYING_TIME && dying_start != 0)
		isDeleted = true;
	if (state == PIRANHAPLANT_STATE_DEATH)
		return;
	CGameObject::Update(dt, coObjects);

	y += vy * dt;

	if (y <= limitY && vy < 0)
	{
		y = limitY;
		SetState(PIRANHAPLANT_STATE_BITING);
	}
	if (y >= limitY + PIRANHAPLANT_BBOX_HEIGHT && vy > 0)
	{
		y = limitY + PIRANHAPLANT_BBOX_HEIGHT;
		SetState(PIRANHAPLANT_STATE_INACTIVE);
	}
	if (GetTickCount64() - biting_start >= PIRANHAPLANT_BITING_TIME && biting_start != 0)
	{
		if (y == limitY)
			vy = PIRANHAPLANT_DARTING_SPEED;
		//vy = 0;
		biting_start = 0;
	}
}

void PiranhaPlant::Render()
{
	int aniId = PIRANHAPLANT_ANI_DEATH;
	if (state != PIRANHAPLANT_STATE_DEATH && dying_start == 0)
		aniId = PIRANHAPLANT_ANI_DARTING;
	CAnimations::GetInstance()->Get(aniId)->Render(nx, x, y);

	RenderBoundingBox();
}

void PiranhaPlant::SetState(int _state)
{
	CGameObject::SetState(_state);
	switch (_state)
	{
	case PIRANHAPLANT_STATE_DARTING:
		vy = -PIRANHAPLANT_DARTING_SPEED;
		//SetType(MOVING);
		break;
	case PIRANHAPLANT_STATE_BITING:
		vy = 0;
		StartBitting();
		break;
	case PIRANHAPLANT_STATE_DEATH:
		vy = 0;
		StartDying();
		break;
	case PIRANHAPLANT_STATE_INACTIVE:
		vy = 0;
		StartBitting();
		break;
	}
}