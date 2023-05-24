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
#define ID_ANI_PIRANHA_PLANT_RED_LEFT_UP 12002
#define ID_ANI_PIRANHA_PLANT_RED_RIGHT_DOWN 12003
#define ID_ANI_PIRANHA_PLANT_RED_RIGHT_UP 12004

#define ID_ANI_PIRANHA_PLANT_GREEN_LEFT_DOWN 12101
#define ID_ANI_PIRANHA_PLANT_GREEN_LEFT_UP 12102
#define ID_ANI_PIRANHA_PLANT_GREEN_RIGHT_DOWN 12103
#define ID_ANI_PIRANHA_PLANT_GREEN_RIGHT_UP 12104

#define ID_ANI_PIRANHA_PLANT_GREEN_NO_SHOOT 12200

class CPiranhaPlant : public CGameObject
{
protected:
	BOOLEAN PlantColor; //0: Red; 1: Green
	BOOLEAN CanShootFire; //0: No; 1: Yes
	BOOLEAN isActivate; //0:No activate; 1: Activate

	float y_start;
	float y_end;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CPiranhaPlant(float x, float y, BOOLEAN PlantColor, BOOLEAN CanShootFire, int state);
	virtual void SetState(int state);
};