#include "WorldMapObjects.h"
#include "WorldPlayer.h"
#include "WorldScene.h"

CWorldMapObject::CWorldMapObject(int sceneId)
{
	vx = vy = 0;
	SetMove(false, false, false, false);
	this->sceneId = sceneId;
	this->option_tag = option_tag;
}

int CWorldMapObject::GetAni(int option_tag) {
	int ani = -1;
	if (option_tag == 1)
		ani = PORTAL_ANI_ID_1;
	else if (option_tag == 2)
		ani = PORTAL_ANI_ID_2;
	else if (option_tag == 3)
		ani = PORTAL_ANI_ID_3;
	else if (option_tag == 4)
		ani = PORTAL_ANI_ID_4;
	else if (option_tag == 5)
		ani = PORTAL_ANI_ID_5;
	else if (option_tag == 6)
		ani = PORTAL_ANI_ID_6;
	else if (option_tag == 7)
		ani = PORTAL_ANI_ID_7;
	else if (option_tag == 8)
		ani = PORTAL_ANI_ID_8;
	else if (option_tag == 9)
		ani = PORTAL_ANI_ID_9;
	return ani;
}

void CWorldMapObject::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (tag == OBJECT_TYPE_PORTAL)
	{
		animations->Get(GetAni(option_tag))->Render(x, y);
	}

	if (tag == OBJECT_TYPE_HAMMER && vx < 0)
		animations->Get(HAMMER_ANI_ID_LEFT)->Render(x, y);
	if (tag == OBJECT_TYPE_HAMMER && vx > 0)
		animations->Get(HAMMER_ANI_ID_RIGHT)->Render(x, y);

	if (tag == OBJECT_TYPE_BUSH)
		animations->Get(BRUSH_ANI_ID)->Render(x, y);
	if (tag == OBJECT_TYPE_STOP)
		animations->Get(STOPPOINT_ANI_ID)->Render(x, y);

	//RenderBoundingBox();
}
void CWorldMapObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
	if (tag == OBJECT_TYPE_HAMMER && x >= HAMMER_LIMIT_X)
		vx = -vx;
	if (tag == OBJECT_TYPE_HAMMER && x <= HAMMER_LIMIT_X - OBJECT_BBOX_WIDTH * 4)
		vx = -vx;
}
void CWorldMapObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (tag != OBJECT_TYPE_BUSH)
	{
		left = x + 2;
		top = y + 2;
		right = left;
		bottom = top;
	}
}

