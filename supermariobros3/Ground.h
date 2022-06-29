#pragma once
#include "GameObject.h"

#define ANI_GROUND	5001
#define BRICK_BBOX_WIDTH	16
#define BRICK_BBOX_HEIGHT	16

class CGround : public CGameObject
{
	int type = 0;
	int item = 0;

	bool isPushed = false;
public:
	int totalItems = 0;
	CGround(float x = 0, float y = 0);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() {
		return 1;
	}
};