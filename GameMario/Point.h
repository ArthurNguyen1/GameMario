#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_POINT_100	19001
#define ID_ANI_POINT_1000	19002
#define ID_ANI_POINT_1UP	19003

#define POINT_TYPE_100	1
#define POINT_TYPE_1000	2
#define POINT_TYPE_1UP	3


#define POINT_SPEED_Y 0.05f

class CPoint : public CGameObject {
private:
	int type; //1: point 100; 2:point 1000; 3: point 1up
	float y_end;
public:
	CPoint(float x, float y, int type) : CGameObject(x, y)
	{
		this->type = type;
		y_end = y - 32;

		vy = -POINT_SPEED_Y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; };
};