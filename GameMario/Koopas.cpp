#include "Koopas.h"

#include "PlayScene.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "PlayScene.h"

#include "InvinsibleBlock.h"

CKoopas::CKoopas(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	form = KOOPAS_NORMAL_FORM;
	isTimeout = 0;
	shell_start_timeout = -1;
	SetState(KOOPAS_STATE_WALKING_LEFT);
	isHeld = 0;
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (form == KOOPAS_SHELL_FORM)
	{
		left = x - KOOPAS_SHELL_BBOX_WIDTH / 2;
		top = y - KOOPAS_SHELL_BBOX_HEIGHT / 2;
		right = left + KOOPAS_SHELL_BBOX_WIDTH;
		bottom = top + KOOPAS_SHELL_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (isTimeout == 1)
	{
		if (GetTickCount64() - shell_start_timeout > KOOPAS_SHELL_START_TIMEOUT && GetTickCount64() - shell_start_timeout <= KOOPAS_SHELL_TIMEOUT)
		{
			SetState(KOOPAS_STATE_SHELL_TIMEOUT);
		}
		else if (GetTickCount64() - shell_start_timeout > KOOPAS_SHELL_TIMEOUT)
		{
			if (nx < 0)
			{
				SetState(KOOPAS_STATE_WALKING_LEFT);
				SetFormation(KOOPAS_NORMAL_FORM);
			}
			else if (nx > 0)
			{
				SetState(KOOPAS_STATE_WALKING_RIGHT);
				SetFormation(KOOPAS_NORMAL_FORM);
			}

			mario->StopUntouchable();
			if (isHeld == 1 && mario->IsPressKeyA() == 1 && mario->GetHoldingState() == 1)
			{
				int level;
				mario->GetLevel(level);
				mario->SetLevel(--level);
			}

			StopTickingTimeout();
			mario->IsNoLongerActuallyHolding();
		}
	}

	int mario_nx = 0;
	mario->GetDirection(mario_nx);

	if (isHeld == 1 && mario->IsPressKeyA() == 1 && mario->GetHoldingState() == 1)
	{
		float mario_x = 0, mario_y = 0;
		mario->GetPosition(mario_x, mario_y);

		if (mario_nx >= 0)
		{
			x = mario_x + 10;
			y = mario_y + 3;
		}
		else
		{
			x = mario_x - 10;
			y = mario_y + 3;
		}
	}
	else if (isHeld == 1 && mario->IsPressKeyA() == 0)
	{
		StopTickingTimeout();

		mario->StartUntouchable();
		mario->IsNoLongerActuallyHolding();
		mario->StartKicking();
		if(mario_nx >= 0)
			SetState(KOOPAS_STATE_SHELL_ROLL_RIGHT);
		else
			SetState(KOOPAS_STATE_SHELL_ROLL_LEFT);
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = -vx;
			nx = -nx;
			if (state == KOOPAS_STATE_WALKING_LEFT)
				SetState(KOOPAS_STATE_WALKING_RIGHT);
			else if (state == KOOPAS_STATE_WALKING_RIGHT)
				SetState(KOOPAS_STATE_WALKING_LEFT);
		}
	if (dynamic_cast<CGoomba*>(e->obj) && form == KOOPAS_SHELL_FORM) 
		e->obj->SetState(GOOMBA_STATE_DIE);
	else if (dynamic_cast<CInvinsibleBlock*>(e->obj) && form == KOOPAS_NORMAL_FORM)
		OnCollisionWithInvinsibleBlock(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj) && form == KOOPAS_SHELL_FORM)
		OnCollisionWithQuestionBlock(e);
}

void CKoopas::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	if (e->nx != 0 && e->obj->GetState() != QUESTION_BLOCK_STATE_EMPTY)
	{
		CQuestionBlock* questionblock = dynamic_cast<CQuestionBlock*>(e->obj);
		float xx, yy;
		questionblock->GetPosition(xx, yy);
		questionblock->SetState(QUESTION_BLOCK_STATE_EMPTY);

		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

		int mario_level;
		mario->GetLevel(mario_level);


		if (mario_level == MARIO_LEVEL_SMALL && questionblock->GetType() == QUESTION_BLOCK_TYPE_SPECIAL_ITEM)
		{
			CGameObject* obj = NULL;

			obj = new CMushroom(xx, yy - 1, MUSHROOM_TYPE_NORMAL);

			obj->SetPosition(xx, yy - 1);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->InsertObject(obj);
		}
		else if (mario_level >= MARIO_LEVEL_BIG && questionblock->GetType() == QUESTION_BLOCK_TYPE_SPECIAL_ITEM)
		{
			CGameObject* obj = NULL;

			obj = new CLeaf(xx, yy - 8);

			obj->SetPosition(xx, yy - 8);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
		}
	}

}

void CKoopas::OnCollisionWithInvinsibleBlock(LPCOLLISIONEVENT e)
{
	if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
		if (state == KOOPAS_STATE_WALKING_LEFT)
			SetState(KOOPAS_STATE_WALKING_RIGHT);
		else if (state == KOOPAS_STATE_WALKING_RIGHT)
			SetState(KOOPAS_STATE_WALKING_LEFT);
	}
}


void CKoopas::Render()
{
	int aniId = -1;
	if (state == KOOPAS_STATE_WALKING_LEFT)
	{
		aniId = ID_ANI_KOOPAS_WALKING_LEFT;
	}
	else if(state == KOOPAS_STATE_WALKING_RIGHT)
	{
		aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	}
	else if (state == KOOPAS_STATE_SHELL_IDLE)
	{
		aniId = ID_ANI_KOOPAS_SHELL_IDLE;
	}
	else if (state == KOOPAS_STATE_SHELL_ROLL_LEFT || state == KOOPAS_STATE_SHELL_ROLL_RIGHT)
	{
		aniId = ID_ANI_KOOPAS_SHELL_ROLL;
	}
	else if (state == KOOPAS_STATE_SHELL_TIMEOUT)
	{
		aniId = ID_ANI_KOOPAS_SHELL_TIMEOUT;
	}
	else if (state == KOOPAS_STATE_SHELL_REVERSE_IDLE)
	{
		aniId = ID_ANI_KOOPAS_SHELL_REVERSE_IDLE;
	}
	else if (state == KOOPAS_STATE_SHELL_REVERSE_ROLL_LEFT || state == KOOPAS_STATE_SHELL_REVERSE_ROLL_RIGHT)
	{
		aniId = ID_ANI_KOOPAS_SHELL_REVERSE_ROLL;
	}
	else if (state == KOOPAS_STATE_SHELL_REVERSE_TIMEOUT)
	{
		aniId = ID_ANI_KOOPAS_SHELL_REVERSE_TIMEOUT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	switch (state)
	{
	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		nx = -1;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		nx = 1;
		break;
	case KOOPAS_STATE_SHELL_IDLE:
		vx = 0;
		break;
	case KOOPAS_STATE_SHELL_ROLL_LEFT:
		vx = -KOOPAS_ROLLING_SPEED;
		nx = -1;
		break;
	case KOOPAS_STATE_SHELL_ROLL_RIGHT:
		vx = KOOPAS_ROLLING_SPEED;
		nx = 1;
		break;
	case KOOPAS_STATE_SHELL_TIMEOUT:
		vx = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CKoopas::SetFormation(int f)
{
	// Adjust position to avoid falling off platform
	if (this->form == KOOPAS_SHELL_FORM)
	{
		y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_SHELL_BBOX_HEIGHT) / 2;
	}
	else if (this->form == KOOPAS_NORMAL_FORM)
	{
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_SHELL_BBOX_HEIGHT) / 2;
	}

	form = f;
}