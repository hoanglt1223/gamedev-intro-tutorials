#include "Leaf.h"
#include "Mario.h"
#include "PlayScene.h"

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + LEAF_BBOX_WIDTH;
	b = y + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnNoCollision(DWORD dt) {
	/*x += vx * dt;
	y += vy * dt;*/
}

void CLeaf::Render()
{
	if (isDeleted)
		return;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(LEAF_ANI_ID)->Render(x, y);
	RenderBoundingBox();
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);

	x += vx * dt;
	y += vy * dt;

	if (state == LEAF_STATE_FALLING) {
		if (GetTickCount64() - start_timing >= LEAF_FALLING_TIME) {
			vx = -vx;
			StartTiming();
		}
	}
	if (state == LEAF_STATE_UP) {

		if (start_y - y >= LEAF_UP_HEIGHT) {
			SetState(LEAF_STATE_FALLING);
		}
	}
}

void CLeaf::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_IDLE:
		vx = vy = 0;
		break;
	case LEAF_STATE_UP:
		vy = -LEAF_SPEED_UP;
		vx = 0;
		start_y = y;
		break;
	case LEAF_STATE_FALLING:
		vy = LEAF_GRAVITY;
		vx = LEAF_SPEED;
		StartTiming();
		break;
	}
}