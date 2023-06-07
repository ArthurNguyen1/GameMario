#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


class CGrass : public CGameObject {
private:
	int spriteId;
public:
	CGrass(float x, float y, int sprite_id) : CGameObject(x, y) 
	{
		this->spriteId = sprite_id;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	
	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }
};