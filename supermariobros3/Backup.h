#pragma once
#include"Mario.h"
class CBackUp
{
public:
	static CBackUp* __instance;
	int life = 4;
	int money = 0;
	DWORD time = 0;
	int score = 0;
	int level = MARIO_LEVEL_SMALL;
	int scene = 0;
	vector<int>cards;
	static CBackUp* GetInstance();
	void BackUpMario(CMario* mario);
	void LoadBackUp(CMario* mario);
};
