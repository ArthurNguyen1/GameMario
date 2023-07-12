#include "Tail.h"

#include "Goomba.h"
#include "Koopas.h"
#include "Point.h"

#include "PlayScene.h"

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MARIO_TAIL_BBOX_WIDTH / 2;
	top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
	right = left + MARIO_TAIL_BBOX_WIDTH;
	bottom = top + MARIO_TAIL_BBOX_HEIGHT;
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	float xx = 0, yy = 0;
	mario->GetPosition(xx, yy);

	x = xx;
	y = yy + 6;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj) && isActivate == 1)
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj) && isActivate == 1)
		OnCollisionWithKoopas(e);
}

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->nx != 0)
	{
		CGameObject* obj = NULL;
		obj = new CPoint(x, y - 16, POINT_TYPE_100);

		obj->SetPosition(x, y - 16);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);

		goomba->SetLevel(GOOMBA_LEVEL_WALK);
		goomba->SetState(GOOMBA_STATE_DIE_REVERSE);
		

		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->StopHitting();
	}	
}

void CTail::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	if (e->nx < 0)
	{
		koopas->IsReverse();

		if (koopas->GetState() == KOOPAS_STATE_WALKING_LEFT || koopas->GetState() == KOOPAS_STATE_WALKING_RIGHT)
		{
			koopas->SetState(KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT);
			koopas->SetFormation(KOOPAS_SHELL_FORM);
			koopas->StartTickingReverseTimeout();
		}
		else if (koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT || koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT || koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_IDLE || koopas->GetState() == KOOPAS_STATE_SHELL_IDLE)
		{
			koopas->SetState(KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT);
			koopas->SetFormation(KOOPAS_SHELL_FORM);
			koopas->StartTickingReverseTimeout();
		}
		else if (koopas->GetState() == KOOPAS_STATE_SHELL_ROLL_LEFT || koopas->GetState() == KOOPAS_STATE_SHELL_ROLL_RIGHT || koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_ROLL_LEFT || koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_ROLL_RIGHT)
		{
			koopas->SetState(KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT);
			koopas->SetFormation(KOOPAS_SHELL_FORM);
			koopas->StartTickingReverseTimeout();
		}
	}
	else
	{
		koopas->IsReverse();

		if (koopas->GetState() == KOOPAS_STATE_WALKING_LEFT || koopas->GetState() == KOOPAS_STATE_WALKING_RIGHT)
		{
			koopas->SetState(KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT);
			koopas->SetFormation(KOOPAS_SHELL_FORM);
			koopas->StartTickingReverseTimeout();
		}
		else if (koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT || koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT || koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_IDLE || koopas->GetState() == KOOPAS_STATE_SHELL_IDLE)
		{
			koopas->SetState(KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT);
			koopas->SetFormation(KOOPAS_SHELL_FORM);
			koopas->StartTickingReverseTimeout();
		}
		else if (koopas->GetState() == KOOPAS_STATE_SHELL_ROLL_LEFT || koopas->GetState() == KOOPAS_STATE_SHELL_ROLL_RIGHT || koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_ROLL_LEFT || koopas->GetState() == KOOPAS_STATE_SHELL_REVERSE_ROLL_RIGHT)
		{
			koopas->SetState(KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT);
			koopas->SetFormation(KOOPAS_SHELL_FORM);
			koopas->StartTickingReverseTimeout();
		}
	}
}


void CTail::Render()
{
	RenderBoundingBox();
}