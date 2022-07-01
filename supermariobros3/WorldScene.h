#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "WorldPlayer.h"
#include "GameObject.h"
#include "Map.h"
#include "HUD.h"

#define OBJECT_TYPE_PLAYER 0
#define OBJECT_TYPE_STOP 2
#define OBJECT_TYPE_PORTAL 3
class CWorldScene : public CScene
{
protected:
	CWorldPlayer* player = NULL;
	CMap* current_map = NULL;
	CHud* hud = NULL;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_MAP(string line);
	void LoadAssets(LPCWSTR assetFile);


public:
	CWorldScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CWorldPlayer* GetPlayer() { return player; }
	CMap* GetMap() { return current_map; }
	CHud* GetHUD() { return hud; }
	//friend class CWorldSceneKeyHandler;
};

class CWorldSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CWorldSceneKeyHandler(CScene* s) :CSceneKeyHandler(s) {};
};