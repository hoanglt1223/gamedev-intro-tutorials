#include "Brick.h"
#include "Mario.h"
#include "Mushroom.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Leaf.h"
#include "BreakPiece.h"

CBrick::CBrick(float x, float y, int type) : CGameObject(x, y)
{
	this->type = type;
	isHit = false;
	SetState(BRICK_STATE_DEFAULT);
	timer = 0;
}

void CBrick::Render()
{
	if (isDeleted)
		return;

	CAnimations* animations = CAnimations::GetInstance();

	int aniId = ID_ANI_BRICK_QUESTION_MARK;
	if (state == BRICK_STATE_EMPTY) aniId = ID_ANI_BRICK_QUESTION_EMPTY;
	if (this->type == BRICK_BREAKABLE) {
		aniId = ID_ANI_BRICK_BREAKABLE;
	}

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::Break() {
	CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CAnimations* animation_sets = CAnimations::GetInstance();
	

	BreakPiece* bPieceTopLeft = new BreakPiece(-1, 1);
	bPieceTopLeft->SetPosition(x, y);

	BreakPiece* bPieceBottomLeft = new BreakPiece(-1, -1);
	bPieceBottomLeft->SetPosition(x, y);

	BreakPiece* bPieceTopRight = new BreakPiece(1, 1);
	bPieceTopRight->SetPosition(x, y);

	BreakPiece* bPieceBottomRight = new BreakPiece(1, -1);
	bPieceBottomRight->SetPosition(x, y);

	currentScene->AddObject(bPieceTopLeft);
	currentScene->AddObject(bPieceBottomLeft);
	currentScene->AddObject(bPieceTopRight);
	currentScene->AddObject(bPieceBottomRight);

	isDeleted = true;
}

void CBrick::Hit()
{
	DebugOut(L"BRICK TYPE: %d \n", type);
	if (state == BRICK_STATE_EMPTY) return;
	LPSCENE scene = CGame::GetInstance()->GetCurrentScene();
	SetState(BRICK_STATE_EMPTY);

	switch (type)
	{
	case BRICK_COIN:
	{
		
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		CGameObject* m = new CCoin(x, y);
		((LPPLAYSCENE)scene)->AddObject(m);
		m->SetState(COIN_STATE_UP);
		mario->AddCoin();
		break;
	}
	case BRICK_POWER_UP:
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		CGameObject* m = nullptr;
		if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
			m = new CMushroom(x, y - MUSHROOM_GROWING_HEIGHT, MUSHROOM_POWERUP);
		}
		if (mario->GetLevel() == MARIO_LEVEL_BIG || mario->GetLevel() == MARIO_LEVEL_RACOON) {
			m = new CLeaf();
			m->SetPosition(x, y);
			m->SetState(LEAF_STATE_UP);
		}
		((LPPLAYSCENE)scene)->AddObject(m);
		break;
	}
	}
}

