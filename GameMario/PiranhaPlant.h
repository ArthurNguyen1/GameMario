#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define PIRANHA_PLANT_SPEED_Y 0.05f

#define PIRANHA_PLANT_BBOX_WIDTH 16
#define PIRANHA_PLANT_BBOX_HEIGHT 32

#define PIRANHA_PLANT_STATE_LEFT 1200
#define PIRANHA_PLANT_STATE_RIGHT 1201

#define ID_ANI_PIRANHA_PLANT_RED_LEFT_DOWN 12001
#define ID_ANI_PIRANHA_PLANT_RED_LEFT_DOWN 12002


class CPiranhaPlant : public CGameObject
{
protected:
	float y_start;
	float y_end;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CPiranhaPlant(float x, float y);
	virtual void SetState(int state);
};