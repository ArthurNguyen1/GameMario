#include "Worldmap1_Turtle.h"

//

void CWorldmap1_Turtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (x > x_end)
	{
		x = x_end;
		vx = -vx;
	}
	else if (x < x_start)
	{
		x = x_start;
		vx = -vx;
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CWorldmap1_Turtle::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_WORLDMAP_TURTLE)->Render(x, y);

	RenderBoundingBox();
}