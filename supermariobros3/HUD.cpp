#include <string>

#include "Game.h"
#include "HUD.h"
#include "Debug.h"
#include "Mario.h"

CHud::CHud()
{
	background = CTextures::GetInstance()->Get(ID_TEX_BLACK);
	statsHUD = CSprites::GetInstance()->Get(STATS);
	powerupHUD = CSprites::GetInstance()->Get(POWERUP);
	arrowEmpty = CSprites::GetInstance()->Get(ARROW_EMPTY);
	arrowFilled = CSprites::GetInstance()->Get(ARROW_FILLED);
	powerEmpty = CSprites::GetInstance()->Get(POWER_EMPTY);
	powerFilled = CSprites::GetInstance()->Get(POWER_FILLED);

	// Set default HUD values
	font = new CFont();
	SetPowerMeter(0);
	offset_y = SCREEN_HEIGHT - 45;
}

void CHud::Render()
{
	CGame* game = CGame::GetInstance();
	CGame::GetInstance()->GetCamPos(x, y);
	x = floor(x); y = floor(y);


	// Render HUD containers textures
	CGame::GetInstance()->Draw(0, offset_y, background, 0, 0, game->GetScreenWidth(), 36);
	statsHUD->Draw(x + 86, y + offset_y - 3);
	powerupHUD->Draw(x + SCREEN_WIDTH - 48, y + offset_y - 3);

	// Render power meter
	for (int i = powerMeter; i < MAX_POWER_METER - 1; i++)
		arrowEmpty->Draw(x + 58 + FONT_SIZE * i, y + offset_y - 5.5f);

}

void CHud::SetPowerMeter(int p)
{
	powerMeter = p;
}

void CHud::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	return;
}