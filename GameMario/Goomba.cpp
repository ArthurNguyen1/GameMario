#include "Goomba.h"

#include "debug.h"

CGoomba::CGoomba(float x, float y, BOOLEAN color, int level) :CGameObject(x, y)
{
	this->vx = -GOOMBA_WALKING_SPEED;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	this->color = color;
	die_start = -1;
	isWalking = isReadyToJump1 = isReadyToJump2 = isReadyToJump3 = isJumping = 0;
	walking_start = ready_to_jump_start1 = ready_to_jump_start2 = ready_to_jump_start3 = jumping_start = -1;
	SetState(GOOMBA_STATE_WALKING);
	SetLevel(level);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (level == GOOMBA_LEVEL_JUMP)
	{
		left = x - GOOMBA_HAS_WINGS_BBOX_WIDTH / 2;
		top = y - GOOMBA_HAS_WINGS_BBOX_HEIGHT / 2;
		right = left + GOOMBA_HAS_WINGS_BBOX_WIDTH;
		bottom = top + GOOMBA_HAS_WINGS_BBOX_HEIGHT;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if (level == GOOMBA_LEVEL_JUMP)
	{
		if (isWalking == 1)
		{
			SetState(GOOMBA_STATE_WALKING);
			if (GetTickCount64() - walking_start >= GOOMBA_WALKING_TIMEOUT)
			{
				SetState(GOOMBA_STATE_READY_TO_JUMP);
				StopWalking();
				StartReadyToJump1();
			}
		}
		else if (isReadyToJump1 == 1)
		{
			if (GetTickCount64() - ready_to_jump_start1 >= GOOMBA_READY_TO_JUMP_TIMEOUT)
			{
				SetState(GOOMBA_STATE_READY_TO_JUMP);
				StopReadyToJump1();
				StartReadyToJump2();
			}
		}
		else if (isReadyToJump2 == 1)
		{
			if (GetTickCount64() - ready_to_jump_start2 >= GOOMBA_READY_TO_JUMP_TIMEOUT)
			{
				SetState(GOOMBA_STATE_READY_TO_JUMP);
				StopReadyToJump2();
				StartReadyToJump3();
			}
		}
		else if (isReadyToJump3 == 1)
		{
			if (GetTickCount64() - ready_to_jump_start3 >= GOOMBA_READY_TO_JUMP_TIMEOUT)
			{
				SetState(GOOMBA_STATE_JUMPING);
				StopReadyToJump3();
				StartJumping();
			}
		}
		else if (isJumping == 1)
		{
			if (GetTickCount64() - jumping_start >= GOOMBA_JUMPING_TIMEOUT)
			{
				SetState(GOOMBA_STATE_WALKING);
				StopJumping();
				StartWalking();
			}
		}
	}

	/*DebugOut(L"[GOOMBA] UPDATE -> state: %d\n", state);
	DebugOut(L"[GOOMBA] UPDATE-> vy: %d\n", vy);
	DebugOut(L"[GOOMBA] UPDATE -> walking_start: %d\n",walking_start);
	DebugOut(L"[GOOMBA] UPDATE -> ready_to_jump_start: %d\n", ready_to_jump_start);
	DebugOut(L"[GOOMBA] UPDATE -> jumping_start: %d\n", jumping_start);
	DebugOut(L"[GOOMBA] UPDATE -> get_tick: %d\n", GetTickCount64());*/


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = -1;

	if (level == GOOMBA_LEVEL_JUMP)
	{
		if (state == GOOMBA_STATE_WALKING)
			aniId = ID_ANI_GOOMBA_RED_HAS_WINGS_WALKING;
		else if (state == GOOMBA_STATE_READY_TO_JUMP)
			aniId = ID_ANI_GOOMBA_RED_HAS_WINGS_JUMPING;
		else
			aniId = ID_ANI_GOOMBA_RED_HAS_WINGS_FLYING;
	}
	else if (level == GOOMBA_LEVEL_WALK)
	{
		if (color == 0)
		{
			if (state == GOOMBA_STATE_DIE)
			{
				aniId = ID_ANI_GOOMBA_DIE;
			}
			else
				aniId = ID_ANI_GOOMBA_WALKING;
		}
		else
		{
			if (state == GOOMBA_STATE_DIE)
			{
				aniId = ID_ANI_GOOMBA_RED_DIE;
			}
			else
				aniId = ID_ANI_GOOMBA_RED_HAS_NO_WINGS_WALKING;
		}
	}

	//DebugOut(L"[GOOMBA] RENDER-> ID: %d\n", aniId);

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vy = 0;
		ay = GOOMBA_GRAVITY;
		break;
	case GOOMBA_STATE_READY_TO_JUMP:
		vy = -GOOMBA_READY_TO_JUMP_SPEED_Y;
		ay = GOOMBA_GRAVITY;
		break;
	case GOOMBA_STATE_JUMPING:
		vy = -GOOMBA_JUMPING_SPEED_Y;
		ay = GOOMBA_GRAVITY;
		break;
	}
}

void CGoomba::SetLevel(int level)
{
	switch (level)
	{
	case GOOMBA_LEVEL_WALK:
		StopWalking();
		StopReadyToJump1();
		StopReadyToJump2();
		StopReadyToJump3();
		StopJumping();
		break;

	case GOOMBA_LEVEL_JUMP:
		StartWalking();
		break;
	}

	this->level = level;
}
