#pragma once

#include "GameObject.h"

#include "AssetIDs.h"

class CCloudBackground : public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBeginTop, spriteIdBeginBot, spriteIdMiddleTop, spriteIdMiddleBot, spriteIdEndTop, spriteIdEndBot;

public:
	CCloudBackground(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin_top, int sprite_id_begin_bot, 
		int sprite_id_middle_top, int sprite_id_middle_bot,
		int sprite_id_end_top, int sprite_id_end_bot) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBeginTop = sprite_id_begin_top;
		this->spriteIdBeginBot = sprite_id_begin_bot;
		this->spriteIdMiddleTop = sprite_id_middle_top;
		this->spriteIdMiddleBot = sprite_id_middle_bot;
		this->spriteIdEndTop = sprite_id_end_top;
		this->spriteIdEndBot = sprite_id_end_bot;

		ObjectType = OBJECT_TYPE_CLOUD_BACKGROUND;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};

	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }
};
