#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MUSHROOM 15000

#define MUSHROOM_WIDTH 16
#define MUSHROOM_HEIGHT 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_SPEED_X 0.04f
#define MUSHROOM_SPEED_Y 0.02f

#define MUSHROOM_GRAVITY 0.002f

class CMushroom : public CGameObject {
protected:
	float y_start;
	float y_end;
	BOOLEAN isAlreadyMovedOutOfBlock;

	float ax;
	float ay;

	void OnCollisionWithMario(LPCOLLISIONEVENT e);
public:
	CMushroom(float x, float y) : CGameObject(x, y)
	{
		y_start = y + 0.5;
		y_end = y - 15;
		vy = -MUSHROOM_SPEED_Y;
		vx = 0.0f;
		isAlreadyMovedOutOfBlock = 0;
		this->ax = 0;
		this->ay = MUSHROOM_GRAVITY;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	bool IsOutOfBlock() { return this->isAlreadyMovedOutOfBlock; }

	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
};