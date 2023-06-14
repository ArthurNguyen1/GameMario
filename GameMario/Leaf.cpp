#include "Leaf.h"

#include "debug.h"


void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;


	if (isStartFalling == 1)
	{
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
	}
	else
	{
		if (y <= y_end)
		{
			y = y_end;
			isStartFalling = 1;
			vx = LEAF_SPEED_X;
			vy = LEAF_SPEED_Y;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = -1;

	if (isStartFalling == 0)
	{
		aniId = ID_ANI_LEAF_LEFT_TO_RIGHT;
	}
	else
	{
		if (vx >= 0)
			aniId = ID_ANI_LEAF_LEFT_TO_RIGHT;
		else
			aniId = ID_ANI_LEAF_RIGHT_TO_LEFT;
	}

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}