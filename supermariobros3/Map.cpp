#include "Map.h"

CMap::CMap(LPCWSTR path) {
	std::ifstream f;
	f.open(path);
	if (!f) DebugOut(L"[ERROR] Unable to load map!\n");

	f >> texturePath >> textureId >>
		mapRows >> mapColumns >>
		tilesheetRows >> tilesheetColumns >>
		tileWidth >> tileHeight >>
		mapStart >> mapEnd >>
		secretStart >> secretEnd;

	LoadTextures();
	tiles = new int* [mapRows];
	for (int i = 0; i < mapRows; i++)
	{
		tiles[i] = new int[mapColumns];
		for (int j = 0; j < mapColumns; j++)
			f >> tiles[i][j];
	}

	f.close();
	DebugOut(L"[INFO] Done loading map data %s\n", path);

}

void CMap::LoadTextures()
{
	CTextures* texture = CTextures::GetInstance();
	texture->Add(textureId, ToLPCWSTR(texturePath));

	LPTEXTURE textureMap = texture->Get(textureId);

	int previousId = 1;
	for (int i = 0; i < tilesheetRows; i++)
		for (int j = 0; j < tilesheetColumns; j++)
		{
			int spriteId = textureId + previousId;
			sprites->Add(spriteId, tileWidth * j, tileHeight * i, tileWidth * (j + 1) - 1, tileHeight * (i + 1) - 1, textureMap);
			previousId++;
		}

}

void CMap::Render()
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	int startColumn = (int)cx / tileWidth;
	int endColumn = startColumn + (CGame::GetInstance()->GetScreenWidth() / tileWidth);

	for (int i = 0; i < mapRows; i++)
		for (int j = startColumn; j <= endColumn; j++)
			sprites->Get(tiles[i][j] + textureId)->Draw(j * (float)tileWidth, i * (float)tileHeight);
}

CMap::~CMap()
{
}