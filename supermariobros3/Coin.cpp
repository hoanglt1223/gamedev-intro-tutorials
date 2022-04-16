#include "Coin.h"

void CCoin::Render()
{
	if (isDeleted) {
		return;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	RenderBoundingBox();
}

void CCoin::OnNoCollision(DWORD dt) {
	y += vy * dt;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {


	if (isDeleted)
		return;

	y += vy * dt;


	if (state == COIN_STATE_UP)
	{
		if (GetTickCount64() - timing_start >= COIN_FALLING_TIME)
		{
			SetState(COIN_STATE_DOWN);
			StartTiming();
		}
	}
	if (state == COIN_STATE_DOWN)
	{
		if (GetTickCount64() - timing_start >= COIN_FALLING_TIME)
		{
			SetState(COIN_STATE_IDLE);
			Delete();
		}
	}
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_IDLE:
		vx = vy = 0;
		break;
	case COIN_STATE_UP:
		vy = -COIN_SPEED;
		StartTiming();
		break;
	case COIN_STATE_DOWN:
		vy = COIN_SPEED;
		break;
	}
}