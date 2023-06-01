#include "Coin.h"

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type == 0)
	{
		y += vy * dt;
		if (y <= y_end)
		{
			vy = -vy;
			y = y_end;
		}
		else if (y > y_start)
		{
			isDeleted = true;
		}
	}
	else
	{
		//Big coin is not moving
	}
}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if(type == 0)
		animations->Get(ID_ANI_COIN_SMALL)->Render(x, y);
	else
		animations->Get(ID_ANI_COIN_BIG)->Render(x, y);

	RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}