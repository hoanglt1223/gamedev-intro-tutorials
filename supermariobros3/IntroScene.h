#pragma once
#include "Scene.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Mario.h"
#include "Game.h"
#include <dinput.h>

#define OBJECT_TYPE_GROUND		4

#define THREE_X	112
#define THREE_Y	96
#define ARROW_Y 144
#define ARROW_X	70

#define GROUND_WIDTH	256

#define SCROLLING_TIME	2000
#define SWITCH_TIME	300

#define WORLD_SCENE_ID	0

class CIntroScene : public CScene {
public:

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_ASSETS(string line);
	void LoadAssets(LPCWSTR assetFile);

public:
	vector<LPGAMEOBJECT> objects;
	LPANIMATION BackGround;
	LPANIMATION Three;
	LPANIMATION Arrow;
	boolean isSwitch = false;
	CIntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

};

class IntroSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	IntroSceneKeyHandler(CScene* s) :CSceneKeyHandler(s) {};
};