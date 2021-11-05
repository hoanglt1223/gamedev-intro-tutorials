#include "Brick.h"
#include "Mario.h"
#include "Mushroom.h"
#include "PlayScene.h"

CBrick::CBrick(float x, float y, int type) : CGameObject(x, y)
{
	this->type = type;
	isHit = false;
	SetState(BRICK_STATE_DEFAULT);
	timer = 0;
}

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = ID_ANI_BRICK_QUESTION_MARK;
	if (state == BRICK_STATE_EMPTY) aniId = ID_ANI_BRICK_QUESTION_EMPTY;
	
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::Hit()
{
	DebugOut(L"BRICK TYPE: %d \n", type);
	if (state == BRICK_STATE_EMPTY) return;

	SetState(BRICK_STATE_EMPTY);

	switch (type)
	{
	case BRICK_COIN:
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->AddCoin();
		break;
	}
	case BRICK_POWER_UP:
	{
		LPSCENE scene = CGame::GetInstance()->GetCurrentScene();
		CGameObject* m = new CMushroom(x, y - MUSHROOM_GROWING_HEIGHT, MUSHROOM_POWERUP);
		((LPPLAYSCENE)scene)->AddObject(m);
		break;
	}
	}
}

