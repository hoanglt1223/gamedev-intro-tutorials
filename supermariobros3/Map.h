#pragma once

#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "debug.h"


class CMap
{
	CSprites* sprites = CSprites::GetInstance();
	string texturePath;

	int textureId;
	int mapRows, mapColumns;
	int tilesheetRows, tilesheetColumns;
	int tileWidth, tileHeight;
	int mapStart, mapEnd;
	int secretStart, secretEnd;
	int** tiles;

public:
	CMap(LPCWSTR path);
	~CMap();

	void LoadTextures();
	void Render();

};

typedef CMap* LPTILEMAP;