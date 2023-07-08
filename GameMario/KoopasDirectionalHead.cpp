#include "KoopasDirectionalHead.h"

void CKoopasDirectionalHead::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPAS_BBOX_WIDTH / 2;
	top = y - KOOPAS_BBOX_HEIGHT / 2;
	right = left + KOOPAS_BBOX_WIDTH;
	bottom = top + KOOPAS_BBOX_HEIGHT;
}

void CKoopasDirectionalHead::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopasDirectionalHead::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopasDirectionalHead::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
}

void CKoopasDirectionalHead::Render()
{	
	RenderBoundingBox();
}

void CKoopasDirectionalHead::SetState(int state)
{
	switch (state)
	{
	case KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		nx = -1;
		break;
	case KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		nx = 1;
		break;
	}

	CGameObject::SetState(state);
}