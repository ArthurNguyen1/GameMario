#include "Brick.h"

#include "debug.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH/2 + 4;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH - 4;
	b = t + BRICK_BBOX_HEIGHT;

	//DebugOut(L"%f, %f, %f, %f \n", l, t, r, b);
}