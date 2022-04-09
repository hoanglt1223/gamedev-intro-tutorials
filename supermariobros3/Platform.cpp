#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CPlatform::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPlatform::Render()
{
	RenderBoundingBox();
	CAnimations* animations = CAnimations::GetInstance();
	CSprites* s = CSprites::GetInstance();
	float xx = x;
	int diff_x = 8;
	int diff_y = 2;
	int diff_y1 = 10;


	if (length <= 0) return;
	if (type == PLATFORM_GROUND) return;
	switch (type)
	{
	case PLATFORM_GROUND:
		break;
	case PLATFORM_PIPE_HIGH:
		animations->Get(PLATFORM_ANI_PIPE_HIGH)->Render(x + diff_x, y - diff_y);
		break;
	case PLATFORM_PIPE:
		animations->Get(PLATFORM_ANI_PIPE)->Render(x + diff_x, y - diff_y1);
		break;
	default:
		s->Get(this->spriteIdBegin)->Draw(xx, y);
		xx += this->cellWidth;
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdMiddle)->Draw(xx, y);
			xx += this->cellWidth;
		}
		if (length > 1)
			s->Get(this->spriteIdEnd)->Draw(xx, y);
		break;
	}
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->length;
	b = t + this->cellHeight;
}
