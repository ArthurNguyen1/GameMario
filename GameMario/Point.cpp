#include "Point.h"

void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (y < y_end)
	{
		isDeleted = true;
	}
}

void CPoint::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (type == POINT_TYPE_100)
		animations->Get(ID_ANI_POINT_100)->Render(x, y);
	else if(type == POINT_TYPE_1000)
		animations->Get(ID_ANI_POINT_1000)->Render(x, y);
	else
		animations->Get(ID_ANI_POINT_1UP)->Render(x, y);
}