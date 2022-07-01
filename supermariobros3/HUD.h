#pragma once

#include "Sprites.h"
#include "Textures.h"
#include "Font.h"
#include "Animations.h"
#include "GameObject.h"
#define PLAYSCENE_HUD	0
#define WORLDSCENE_HUD	1
enum HUDSprites
{
	STATS = 50001,
	POWERUP = 50002,
	ICON_MARIO = 50003,
	ARROW_FILLED = 50005,
	POWER_FILLED = 50006,
	ARROW_EMPTY = 50007,
	POWER_EMPTY = 50008,
	POWER_ANI = 77,
};


class CHud : public CGameObject
{
	float offset_y;
	float x, y;

	int world, powerMeter;

	CFont* font;
	LPSPRITE stage;
	LPSPRITE statsHUD, powerupHUD, icon;
	LPSPRITE arrowFilled, powerFilled;
	LPSPRITE arrowEmpty, powerEmpty;
	LPTEXTURE background;
	LPANIMATION powerMeterIcon;
	vector<LPSPRITE> score, money, time;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

public:
	CHud();
	virtual void Render();
	void SetPowerMeter(int);
};

