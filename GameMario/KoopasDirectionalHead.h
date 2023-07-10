#pragma once
#include "GameObject.h"

#define KOOPAS_DIRECTIONAL_HEAD_GRAVITY 0.002f
#define KOOPAS_DIRECTIONAL_HEAD_WALKING_SPEED 0.05f

#define KOOPAS_DIRECTIONAL_HEAD_BBOX_WIDTH 16
#define KOOPAS_DIRECTIONAL_HEAD_BBOX_HEIGHT 16

#define KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_LEFT	1421
#define KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_RIGHT	1431

#define KOOPAS_FALLEN_DISTANCE 8


class CKoopasDirectionalHead : public CGameObject
{
protected:
	float ax;
	float ay;

	BOOLEAN isActivate; //0:No; 1:Yes
public:
	CKoopasDirectionalHead(float x, float y, int state) : CGameObject(x, y)
	{
		this->ax = 0;
		this->ay = KOOPAS_DIRECTIONAL_HEAD_GRAVITY;
		SetState(state);
		isActivate = 0;
	}
	void SetState(int state);


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