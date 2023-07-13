#include "Bullet.h"

#include "AssetIDs.h"

CBullet::CBullet(float x, float y, int state) : CGameObject(x,y)
{
	this->state = state;
	if (this->state == BULLET_STATE_LEFT_UP_HIGH)
	{
		vx = -BULLET_SPEED_X;
		vy = -BULLET_SPEED_Y * 5;
	}
	if (this->state == BULLET_STATE_LEFT_UP)
	{
		vx = -BULLET_SPEED_X;
		vy = -BULLET_SPEED_Y * 2;
	}
	if (this->state == BULLET_STATE_LEFT_DOWN)
	{
		vx = -BULLET_SPEED_X;
		vy = BULLET_SPEED_Y;
	}
	if (this->state == BULLET_STATE_LEFT_DOWN_LOW)
	{
		vx = -BULLET_SPEED_X;
		vy = BULLET_SPEED_Y * 3;
	}
	if (this->state == BULLET_STATE_RIGHT_UP_HIGH)
	{
		vx = BULLET_SPEED_X;
		vy = -BULLET_SPEED_Y * 5;
	}
	if (this->state == BULLET_STATE_RIGHT_UP)
	{
		vx = BULLET_SPEED_X;
		vy = -BULLET_SPEED_Y * 2;
	}
	if (this->state == BULLET_STATE_RIGHT_DOWN)
	{
		vx = BULLET_SPEED_X;
		vy = BULLET_SPEED_Y;
	}
	if (this->state == BULLET_STATE_RIGHT_DOWN_LOW)
	{
		vx = BULLET_SPEED_X;
		vy = BULLET_SPEED_Y * 3;
	}

	ObjectType = OBJECT_TYPE_BULLET;
}

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBullet::Render()
{
	int aniId;
	if (state == BULLET_STATE_LEFT_UP_HIGH || state == BULLET_STATE_LEFT_UP || state == BULLET_STATE_LEFT_DOWN || state == BULLET_STATE_LEFT_DOWN_LOW)
	{
		aniId = ID_ANI_BULLET_LEFT;
	}
	else
	{
		aniId = ID_ANI_BULLET_RIGHT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
