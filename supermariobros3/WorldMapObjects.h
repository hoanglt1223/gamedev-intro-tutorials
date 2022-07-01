#pragma once
#include "GameObject.h"

#define OBJECT_TYPE_PLAYER				0
#define OBJECT_TYPE_BRICK				1
#define OBJECT_TYPE_STOP				2
#define OBJECT_TYPE_PORTAL				3
#define OBJECT_TYPE_BUSH				4
#define OBJECT_TYPE_HAMMER				5

#define HAMMER_LIMIT_X		176
#define OBJECT_BBOX_WIDTH	4

#define HAMMER_ANI_ID_RIGHT	420
#define HAMMER_ANI_ID_LEFT	421
#define BRUSH_ANI_ID		401
#define STOPPOINT_ANI_ID	499
#define PORTAL_ANI_ID_1		402
#define PORTAL_ANI_ID_2		403
#define PORTAL_ANI_ID_3		407
#define PORTAL_ANI_ID_4		404
#define PORTAL_ANI_ID_5		408
#define PORTAL_ANI_ID_6		411
#define PORTAL_ANI_ID_7		405
#define PORTAL_ANI_ID_8		406
#define PORTAL_ANI_ID_9		412
class CWorldMapObject :
	public CGameObject
{
	int sceneId;
	int option_tag;
public:
	bool cgLeft, cgRight, cgUp, cgDown;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	CWorldMapObject(int sceneId = -1);
	int GetSceneId() { return sceneId; };
	void SetOptionTag(int tag) {
		option_tag = tag;
	}
	void SetMove(bool cLeft, bool cUp, bool cRight, bool cDown)
	{
		cgLeft = cLeft;
		cgRight = cRight;
		cgUp = cUp;
		cgDown = cDown;
	};
	void GetMove(bool& cLeft, bool& cUp, bool& cRight, bool& cDown)
	{
		cLeft = cgLeft;
		cRight = cgRight;
		cUp = cgUp;
		cDown = cgDown;
	};

	int GetAni(int option);
};

