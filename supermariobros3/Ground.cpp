#include "Ground.h"
#include "Utils.h"

CGround::CGround(float x, float y) :CGameObject() {

}


void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;

}
void CGround::Render()
{
	int diff_X = 125;
	CAnimations::GetInstance()->Get(ANI_GROUND)->Render(x + diff_X, y);
	//RenderBoundingBox();
}
