#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_WORLDMAP_TURTLE 23004

#define TURTLE_SPEED_X 0.004f

class CWorldmap1_Turtle : public CGameObject {
protected:
	float x_start;
	float x_end;
public:
	CWorldmap1_Turtle(float x, float y) : CGameObject(x, y)
	{
		x_start = x;
		x_end = x + 23;
		vx = -TURTLE_SPEED_X;

		ObjectType = OBJECT_TYPE_WORLDMAP_TURTLE;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
};
