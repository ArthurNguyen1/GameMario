#include "PiranhaPlant.h"

CPiranhaPlant::CPiranhaPlant(float x, float y, BOOLEAN PlantColor, BOOLEAN CanShootFire, int state) :CGameObject(x, y)
{
	this->PlantColor = PlantColor;
	this->CanShootFire = CanShootFire;
	this->isActivate = 0;
	SetState(state);

	y_start = y;
	y_end = y - 20;
	this->vy = -PIRANHA_PLANT_SPEED_Y;
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHA_PLANT_BBOX_WIDTH / 2;
	top = y - PIRANHA_PLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHA_PLANT_BBOX_WIDTH;
	bottom = top + PIRANHA_PLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPiranhaPlant::Render()
{
	int aniId = ID_ANI_PIRANHA_PLANT_RED_LEFT_DOWN;
	

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}




