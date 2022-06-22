#include "Switch.h"
#include "Coin.h"
#include "Brick.h"
#include "PlayScene.h"
#include "Platform.h"

void Switch::Render() {
	if (isDeleted)
		return;
	CAnimations* animations = CAnimations::GetInstance();
	if (state == SWITCH_STATE_PRESSED)
		animations->Get(SWITCH_ANI_STOMPED_ID)->Render(x, y);
	else
		animations->Get(SWITCH_ANI_ID)->Render(x, y);
	RenderBoundingBox();
}

void Switch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted)
		return;
	CGameObject::Update(dt);
}

void Switch::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case SWITCH_STATE_UP:
		vy = -0.05f;
		start_y = y;
		break;
	case SWITCH_STATE_PRESSED:
		y += SWITCH_BBOX_HEIGHT - SWITCH_BBOX_PRESSED_HEIGHT;
		ChangeBrickToCoin();
		break;
	}
}

void Switch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + SWITCH_BBOX_WIDTH;
	if (state == SWITCH_STATE_PRESSED)
		b = y + SWITCH_BBOX_PRESSED_HEIGHT;
	else
		b = y + SWITCH_BBOX_HEIGHT;
}

void Switch::ChangeBrickToCoin() {
	CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	vector<LPGAMEOBJECT> objects = currentScene->GetObjects();
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CBrick*>(objects.at(i)) && !objects.at(i)->IsDeleted()) {
			CBrick* bBrick = dynamic_cast<CBrick*>(objects.at(i));
			float bX, bY;
			bBrick->GetPosition(bX, bY);
			if (bBrick->Type() == BRICK_BREAKABLE) {
				CCoin* coin = new CCoin(bX, bY);
				((LPPLAYSCENE)currentScene)->AddObject(coin);
				bBrick->Delete();
			}
		}
		if (dynamic_cast<CPlatform*>(objects.at(i)) && !objects.at(i)->IsDeleted()) {
			CPlatform* platform = dynamic_cast<CPlatform*>(objects.at(i));
			float bX, bY;
			if (platform->GetType() == 5) {
				platform->Delete();
			}
		}
	}
}