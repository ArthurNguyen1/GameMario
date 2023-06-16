#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Koopas.h"
#include "Coin.h"
#include "Portal.h"
#include "ColorBox.h"
#include "QuestionBlock.h"
#include "PiranhaPlant.h"
#include "Bullet.h"
#include "Leaf.h"

#include "Collision.h"

#include "PlayScene.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	//reset kick action
	if (isKicking == 1)
	{
		if (GetTickCount64() - kicking_start > MARIO_KICKING_TIME)
		{
			StopKicking();
		}
		else
		{
			if (nx > 0)
			{
				this->SetState(MARIO_STATE_KICKING_RIGHT);
			}
			else if (nx < 0)
			{
				this->SetState(MARIO_STATE_KICKING_LEFT);
			}		
		}
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<CBullet*>(e->obj))
		OnCollisionWithBullet(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	
	SetLevel(MARIO_LEVEL_HAVE_TAIL);

	e->obj->Delete();

}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetLevel() == GOOMBA_LEVEL_JUMP)
		{
			goomba->SetLevel(GOOMBA_LEVEL_WALK);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}		
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_HAVE_TAIL)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	if (e->ny < 0) // jump on top, only case that mario can hit koopas walking >> turn koopas into shell and deflect a bit 
	{
		if (koopas->GetState() == KOOPAS_STATE_WALKING_LEFT || koopas->GetState() == KOOPAS_STATE_WALKING_RIGHT)
		{
			koopas->SetState(KOOPAS_STATE_SHELL_IDLE);
			koopas->SetFormation(KOOPAS_SHELL_FORM);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			koopas->StartTickingTimeout();
			DebugOut(L"[KOOPAS] HIT FROM {TOP} -> turn NORMAL into SHELL IDLE\n");
		}
		else if (koopas->GetState() == KOOPAS_STATE_SHELL_IDLE)
		{
			koopas->StopTickingTimeout();
			int _nx;
			koopas->GetDirection(_nx);
			if (_nx < 0)
			{
				koopas->SetState(KOOPAS_STATE_SHELL_ROLL_LEFT);
			}
			else if (_nx > 0)
			{
				koopas->SetState(KOOPAS_STATE_SHELL_ROLL_RIGHT);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			StartUntouchable();
			StartKicking();
			DebugOut(L"[KOOPAS] HIT FROM {TOP ONLY} -> turn SHELL IDLE into SHELL ROLLING random side\n");

		}
		else if (koopas->GetState() == KOOPAS_STATE_SHELL_ROLL_LEFT || koopas->GetState() == KOOPAS_STATE_SHELL_ROLL_RIGHT)
		{
			koopas->SetState(KOOPAS_STATE_SHELL_IDLE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			koopas->StartTickingTimeout();
			DebugOut(L"[KOOPAS] HIT FROM {TOP OF ROLLING SHELL} -> turn SHELL ROLLING into SHELL IDLE\n");
		}	
	}
	else if (e->ny > 0) // jump from bot >> can only turn koopas from shell idle into shell rolling and not deflect 
	{
		if (koopas->GetState() == KOOPAS_STATE_SHELL_IDLE)
		{
			koopas->StopTickingTimeout();
			int _nx;
			koopas->GetDirection(_nx);
			if (_nx < 0)
			{
				koopas->SetState(KOOPAS_STATE_SHELL_ROLL_LEFT);
			}
			else if (_nx > 0)
			{
				koopas->SetState(KOOPAS_STATE_SHELL_ROLL_RIGHT);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			StartUntouchable();
			StartKicking();
			DebugOut(L"[KOOPAS] HIT FROM {BOT ONLY} -> turn SHELL IDLE into SHELL ROLLING random side\n");
		}
		else // hit mario
		{
			if (untouchable == 0)
			{
				DebugOut(L"[KOOPAS] HIT MARIO FROM BOT\n");
				if (level == MARIO_LEVEL_HAVE_TAIL)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
	else if (e->nx < 0) 
	{
		if (koopas->GetState() == KOOPAS_STATE_SHELL_IDLE)
		{
			koopas->StopTickingTimeout();
			koopas->SetState(KOOPAS_STATE_SHELL_ROLL_RIGHT);
			StartUntouchable();
			StartKicking();
			DebugOut(L"[KOOPAS] HIT FROM {LEFT} -> turn SHELL IDLE into SHELL IDLE ROLLING ... LEFT TO RIGHT\n");
		}
		else // hit mario
		{
			DebugOut(L"[KOOPAS] HIT MARIO FROM LEFT\n");

			if (untouchable == 0)
			{
				if (level == MARIO_LEVEL_HAVE_TAIL)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
	else if (e->nx > 0)
	{
		if (koopas->GetState() == KOOPAS_STATE_SHELL_IDLE)
		{
			koopas->StopTickingTimeout();
			koopas->SetState(KOOPAS_STATE_SHELL_ROLL_LEFT);
			StartUntouchable();
			StartKicking();
			DebugOut(L"[KOOPAS] HIT FROM {RIGHT} -> turn SHELL IDLE into SHELL IDLE ROLLING ... LEFT TO RIGHT\n");
		}
		else // hit mario
		{
			DebugOut(L"[KOOPAS] HIT MARIO FROM RIGHT\n");
			if (untouchable == 0)
			{
				if (level == MARIO_LEVEL_HAVE_TAIL)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	CPiranhaPlant* piranhaplant = dynamic_cast<CPiranhaPlant*>(e->obj);

	if (untouchable == 0 && piranhaplant->GetActivateState() != 0)
	{
		if (level == MARIO_LEVEL_HAVE_TAIL)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_HAVE_TAIL)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* coin= dynamic_cast<CCoin*>(e->obj);
	if (coin->GetType() == 0)
	{

	}
	else
	{
		e->obj->Delete();
		coin++;
	}	
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CQuestionBlock* questionblock = dynamic_cast<CQuestionBlock*>(e->obj);

	if (e->ny > 0 && questionblock->GetState() != QUESTION_BLOCK_STATE_EMPTY)
	{
		float x, y;
		questionblock->GetPosition(x, y);
		CGameObject* obj = NULL;

		if (questionblock->GetType() == 0)
		{
			obj = new CCoin(x, y - 24, 0);

			obj->SetPosition(x, y - 24);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
		}
		else
		{
			
		}

		questionblock->SetMovingState(true);
		questionblock->SetState(QUESTION_BLOCK_STATE_EMPTY);
		//DebugOut(L"%d\n", questionblock->GetState());
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	
	if (!isOnPlatform)
	{
		if (state == MARIO_STATE_KICKING_RIGHT && level == MARIO_LEVEL_SMALL)
			aniId = ID_ANI_MARIO_SMALL_KICKING_RIGHT;
		else if (state == MARIO_STATE_KICKING_LEFT && level == MARIO_LEVEL_SMALL)
			aniId = ID_ANI_MARIO_SMALL_KICKING_LEFT;
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (state == MARIO_STATE_KICKING_RIGHT && level == MARIO_LEVEL_SMALL)
			aniId = ID_ANI_MARIO_SMALL_KICKING_RIGHT;
		else if (state == MARIO_STATE_KICKING_LEFT && level == MARIO_LEVEL_SMALL)
			aniId = ID_ANI_MARIO_SMALL_KICKING_LEFT;		
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (state == MARIO_STATE_KICKING_RIGHT && level == MARIO_LEVEL_BIG)
			aniId = ID_ANI_MARIO_KICKING_RIGHT;
		else if (state == MARIO_STATE_KICKING_LEFT && level == MARIO_LEVEL_BIG)
			aniId = ID_ANI_MARIO_KICKING_LEFT;
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (state == MARIO_STATE_KICKING_RIGHT && level == MARIO_LEVEL_BIG)
			aniId = ID_ANI_MARIO_KICKING_RIGHT;
		else if (state == MARIO_STATE_KICKING_LEFT && level == MARIO_LEVEL_BIG)
			aniId = ID_ANI_MARIO_KICKING_LEFT;
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for Mario have tail
//
int CMario::GetAniIdHaveTail()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (state == MARIO_STATE_KICKING_RIGHT && level == MARIO_LEVEL_HAVE_TAIL)
			aniId = ID_ANI_MARIO_HAVE_TAIL_KICKING_RIGHT;
		else if (state == MARIO_STATE_KICKING_LEFT && level == MARIO_LEVEL_HAVE_TAIL)
			aniId = ID_ANI_MARIO_HAVE_TAIL_KICKING_LEFT;
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_HAVE_TAIL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_HAVE_TAIL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_HAVE_TAIL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_HAVE_TAIL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_HAVE_TAIL_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_HAVE_TAIL_SIT_LEFT;
		}
		else if (state == MARIO_STATE_KICKING_RIGHT && level == MARIO_LEVEL_HAVE_TAIL)
			aniId = ID_ANI_MARIO_HAVE_TAIL_KICKING_RIGHT;
		else if (state == MARIO_STATE_KICKING_LEFT && level == MARIO_LEVEL_HAVE_TAIL)
			aniId = ID_ANI_MARIO_HAVE_TAIL_KICKING_LEFT;
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_HAVE_TAIL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_HAVE_TAIL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_HAVE_TAIL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_HAVE_TAIL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_HAVE_TAIL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_HAVE_TAIL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_HAVE_TAIL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_HAVE_TAIL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_HAVE_TAIL_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_HAVE_TAIL)
		aniId = GetAniIdHaveTail();

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0.0f; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_KICKING_LEFT:
		break;
	case MARIO_STATE_KICKING_RIGHT:
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_HAVE_TAIL)
	{
		if (isSitting)
		{
			left = x - MARIO_HAVE_TAIL_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_HAVE_TAIL_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_HAVE_TAIL_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_HAVE_TAIL_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_HAVE_TAIL_BBOX_WIDTH / 2;
			top = y - MARIO_HAVE_TAIL_BBOX_HEIGHT / 2;
			right = left + MARIO_HAVE_TAIL_BBOX_WIDTH;
			bottom = top + MARIO_HAVE_TAIL_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	else if (this->level == MARIO_LEVEL_BIG)
	{
		y -= (MARIO_HAVE_TAIL_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT) / 2;
	}
	level = l;
}

