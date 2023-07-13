#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_LEAF_RIGHT_TO_LEFT 16000
#define ID_ANI_LEAF_LEFT_TO_RIGHT 16001

#define LEAF_WIDTH 16
#define LEAF_HEIGHT 14
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14

#define LEAF_SPEED_X 0.04f
#define LEAF_SPEED_Y 0.02f
#define LEAF_SPEED_Y_UP 0.06f

class CLeaf : public CGameObject {
protected:
	float x_start;
	float x_end;
	float y_end;
	BOOLEAN isStartFalling;

	float ax;
	float ay;

public:
	CLeaf(float x, float y) : CGameObject(x, y)
	{
		x_start = x;
		x_end = x + 32;
		y_end = y - 36;
		vy = -LEAF_SPEED_Y_UP;
		vx = 0.0f;
		isStartFalling = 0;
		this->ay = 0;
		this->ax = 0;

		ObjectType = OBJECT_TYPE_LEAF;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
};