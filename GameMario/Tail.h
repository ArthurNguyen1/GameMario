#pragma once
#include "GameObject.h"

#define MARIO_TAIL_BBOX_WIDTH 28
#define MARIO_TAIL_BBOX_HEIGHT 6

class CTail : public CGameObject
{
protected:
	BOOLEAN isActivate; //0:No; 1:Yes

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);

public:
	CTail(float x, float y) : CGameObject(x, y)
	{
		isActivate = 0;
	}
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void IsActivate() { isActivate = 1; }
	void IsNoActivate() { isActivate = 0; }
};