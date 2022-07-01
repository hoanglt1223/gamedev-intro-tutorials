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
	int tileWidth = 16;
	int countTile = 0;
	int totalTiles = 0;
	int** tiles;

public:
	CMap(LPCWSTR path);
	~CMap();

	void LoadTextures();
	void Render();

};

typedef CMap* LPTILEMAP;