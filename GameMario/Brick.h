#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_BRICK 18000
#define ID_ANI_BRICK_SHINE 18001
#define ID_ANI_BRICK_CUT_SCENE 18002
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
private:
	int aniId;
public:
	CBrick(float x, float y, int aniId) : CGameObject(x, y) 
	{ 
		this->aniId = aniId; 
		if (this->aniId == ID_ANI_BRICK_SHINE)
			ObjectType = OBJECT_TYPE_BRICK_SHINE;
		else
			ObjectType = OBJECT_TYPE_BRICK;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; }

};