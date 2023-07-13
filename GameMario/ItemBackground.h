#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

class CItemBackground : public CGameObject {
private:
	int spriteId;
public:
	CItemBackground(float x, float y, int sprite_id) : CGameObject(x, y)
	{
		this->spriteId = sprite_id;
		ObjectType = OBJECT_TYPE_ITEM_BACKGROUND;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }
};