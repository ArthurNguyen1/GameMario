#pragma once

#include "GameObject.h"

#include "AssetIDs.h"

class CColorBox : public CGameObject
{
protected:
	int length;				// Unit: cell 
	int height;
	float cellWidth;
	float cellHeight;
	int spriteIdLeftTop, spriteIdLeftMid, spriteIdLeftBot;
	int spriteIdMiddleTop, spriteIdMiddleMid, spriteIdMiddleBot;
	int spriteIdRightTop, spriteIdRightMid, spriteIdRightBot;

public:
	CColorBox(float x, float y,
		float cell_width, float cell_height, int length, int height,
		int sprite_id_left_top, int sprite_id_left_mid, int sprite_id_left_bot,
		int sprite_id_middle_top, int sprite_id_middle_mid, int sprite_id_middle_bot,
		int sprite_id_right_top, int sprite_id_right_mid, int sprite_id_right_bot) :CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;

		this->spriteIdLeftTop = sprite_id_left_top;
		this->spriteIdLeftMid = sprite_id_left_mid;
		this->spriteIdLeftBot = sprite_id_left_bot;

		this->spriteIdMiddleTop = sprite_id_middle_top;
		this->spriteIdMiddleMid = sprite_id_middle_mid;
		this->spriteIdMiddleBot = sprite_id_middle_bot;

		this->spriteIdRightTop = sprite_id_right_top;
		this->spriteIdRightMid = sprite_id_right_mid;
		this->spriteIdRightBot = sprite_id_right_bot;

		ObjectType = OBJECT_TYPE_COLORBOX;
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	void RenderShade();

	int IsDirectionColliable(float nx, float ny);

};