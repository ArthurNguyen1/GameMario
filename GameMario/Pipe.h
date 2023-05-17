#pragma once

#include "GameObject.h"

class CPipe : public CGameObject
{
protected:
	int height;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdTopLeft, spriteIdTopRight, spriteIdBodyLeft, spriteIdBodyRight;

public:
	CPipe(float x, float y,
		float cell_width, float cell_height, int height,
		int sprite_id_top_left, int sprite_id_top_right, 
		int sprite_id_body_left, int sprite_id_body_right) :CGameObject(x, y)
	{
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdTopLeft = sprite_id_top_left;
		this->spriteIdTopRight = sprite_id_top_right;
		this->spriteIdBodyLeft = sprite_id_body_left;
		this->spriteIdBodyRight = sprite_id_body_right;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};