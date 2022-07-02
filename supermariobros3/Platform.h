#pragma once

#include "GameObject.h"

#define PLATFORM_GROUND 0
#define PLATFORM_SPECIAL 1
#define PLATFORM_PIPE 3
#define PLATFORM_PIPE_HIGH 2
#define PIPE_EXTRA			8
#define PLATFORM_ANI_PIPE 800011
#define PLATFORM_ANI_PIPE_HIGH	800010
#define PIPE_EXTRA_ANI	800012

#define PIPE_DOWN 9
#define PIPE_UP 10
#define PLATFORM_PIPE_HIGH_PORTAL 12
#define PLATFORM_PIPE_PORTAL 13

// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected: 
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int type;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
	int isBlocking = 1;
public: 
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length, int type,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->type = type;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();

	int IsSpecialPlatform() { return (type == PLATFORM_SPECIAL); }

	int GetType() { return this->type; }
	float GetStart() { return this->x; }
	float GetEnd() { return (this->x + this->length * this->cellWidth); }
};

typedef CPlatform* LPPLATFORM;