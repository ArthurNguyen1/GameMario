#include "Koopas.h"

#include "PlayScene.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Brick.h"

#include "ColorBox.h"
#include "Platform.h"

CKoopas::CKoopas(float x, float y, int color, int form) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->color = color;
	this->form = form;
	isOnPlatform = 0;
	isTimeout = 0;
	shell_start_timeout = -1;
	SetState(KOOPAS_STATE_WALKING_LEFT);
	isHeld = 0;
	isReverse = 0;

	ObjectType = OBJECT_TYPE_KOOPAS;

	if (this->color == 0) //only RED koopas has directional head
	{
		if (_directionalHead == NULL)
		{
			if (nx >= 0)
			{
				_directionalHead = new CKoopasDirectionalHead(this->x + KOOPAS_BBOX_WIDTH, this->y, KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_RIGHT);

				CGameObject* obj = NULL;

				obj = _directionalHead;

				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
			}
			else
			{
				_directionalHead = new CKoopasDirectionalHead(this->x - KOOPAS_BBOX_WIDTH, this->y, KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_LEFT);

				CGameObject* obj = NULL;

				obj = _directionalHead;

				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
			}
		}

		if (this->form == KOOPAS_NORMAL_FORM)
			_directionalHead->IsActivate();
		else
			_directionalHead->IsNoActivate();
	}
	else //GREEN
	{
		if (_directionalHead == NULL)
		{
			if (nx >= 0)
			{
				_directionalHead = new CKoopasDirectionalHead(this->x + KOOPAS_BBOX_WIDTH, this->y, KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_RIGHT);
			}
			else
			{
				_directionalHead = new CKoopasDirectionalHead(this->x - KOOPAS_BBOX_WIDTH, this->y, KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_LEFT);
			}
		}
		_directionalHead->IsNoActivate();
	}
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (form == KOOPAS_HAS_WINGS_FORM)
	{
		left = x - KOOPAS_HAS_WINGS_BBOX_WIDTH / 2;
		top = y - KOOPAS_HAS_WINGS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_HAS_WINGS_BBOX_WIDTH;
		bottom = top + KOOPAS_HAS_WINGS_BBOX_HEIGHT;
	}
	else if (form == KOOPAS_SHELL_FORM)
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

void CKoopas::ChangeDirection()
{
	if (state == KOOPAS_STATE_WALKING_LEFT)
	{
		SetState(KOOPAS_STATE_WALKING_RIGHT);
		_directionalHead->SetPosition(this->x + KOOPAS_BBOX_WIDTH, this->y);
		_directionalHead->SetState(KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_RIGHT);
	}
	else if (state == KOOPAS_STATE_WALKING_RIGHT)
	{
		SetState(KOOPAS_STATE_WALKING_LEFT);
		_directionalHead->SetPosition(this->x - KOOPAS_BBOX_WIDTH, this->y);
		_directionalHead->SetState(KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_LEFT);
	}
}

void CKoopas::ResetDirectionalHead()
{
	if (nx < 0)
	{
		SetState(KOOPAS_STATE_WALKING_LEFT);
		_directionalHead->SetPosition(this->x - KOOPAS_BBOX_WIDTH, this->y);
		_directionalHead->SetState(KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_LEFT);
	}
	else //if (nx > 0)
	{
		SetState(KOOPAS_STATE_WALKING_RIGHT);
		_directionalHead->SetPosition(this->x + KOOPAS_BBOX_WIDTH, this->y);
		_directionalHead->SetState(KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_RIGHT);
	}

	_directionalHead->IsActivate();

}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	isOnPlatform = 0;

	//koopas is hold and kicked
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (isReverse == 0) //Normal koopas shell held and roll
	{
		if (isTimeout == 1)
		{
			if (GetTickCount64() - shell_start_timeout > KOOPAS_SHELL_START_TIMEOUT && GetTickCount64() - shell_start_timeout <= KOOPAS_SHELL_TIMEOUT)
			{
				SetState(KOOPAS_STATE_SHELL_TIMEOUT);
			}
			else if (GetTickCount64() - shell_start_timeout > KOOPAS_SHELL_TIMEOUT)
			{
				if (color == 0) //RED
				{
					if (nx < 0)
					{
						SetState(KOOPAS_STATE_WALKING_LEFT);
						SetFormation(KOOPAS_NORMAL_FORM);
						_directionalHead->SetPosition(this->x - KOOPAS_BBOX_WIDTH, this->y);
						_directionalHead->SetState(KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_LEFT);
					}
					else if (nx > 0)
					{
						SetState(KOOPAS_STATE_WALKING_RIGHT);
						SetFormation(KOOPAS_NORMAL_FORM);
						_directionalHead->SetPosition(this->x + KOOPAS_BBOX_WIDTH, this->y);
						_directionalHead->SetState(KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_RIGHT);
					}
				}
				else //GREEN
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
				}

				//mario->StopUntouchable();
				if (isHeld == 1 && mario->IsPressKeyA() == 1 && mario->GetHoldingState() == 1)
				{
					int level;
					mario->GetLevel(level);
					if (level == MARIO_LEVEL_HAVE_TAIL)
					{
						mario->SetLevel(MARIO_LEVEL_BIG);
						mario->StartUntouchable();
						mario->StartTransformationToHasWings();
					}
					else if (level == MARIO_LEVEL_BIG)
					{
						mario->SetLevel(MARIO_LEVEL_SMALL);
						mario->StartUntouchable();
						mario->StartTransformationToSmall();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						mario->SetState(MARIO_STATE_DIE);
					}
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

			int mario_level = 0;
			mario->GetLevel(mario_level);

			if (mario_level == MARIO_LEVEL_SMALL)
			{
				if (mario_nx >= 0)
				{
					x = mario_x + 10;
					y = mario_y - 2;
				}
				else
				{
					x = mario_x - 10;
					y = mario_y - 2;
				}
			}
			else
			{
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
		}
		else if (isHeld == 1 && mario->IsPressKeyA() == 0)
		{
			StopTickingTimeout();

			mario->StartUntouchable();
			mario->IsNoLongerActuallyHolding();
			mario->StartKicking();
			if (mario_nx >= 0)
				SetState(KOOPAS_STATE_SHELL_ROLL_RIGHT);
			else
				SetState(KOOPAS_STATE_SHELL_ROLL_LEFT);
		}
	}
	else //Reverse koopas shell
	{
		if (isTimeout == 1)
		{
			if (GetTickCount64() - shell_start_timeout > KOOPAS_SHELL_START_TIMEOUT && GetTickCount64() - shell_start_timeout <= KOOPAS_SHELL_TIMEOUT)
			{
				SetState(KOOPAS_STATE_SHELL_REVERSE_TIMEOUT);
			}
			else if (GetTickCount64() - shell_start_timeout > KOOPAS_SHELL_TIMEOUT)
			{
				isReverse = 0;
				if (color == 0) //RED
				{
					if (nx < 0)
					{
						SetState(KOOPAS_STATE_WALKING_LEFT);
						SetFormation(KOOPAS_NORMAL_FORM);
						_directionalHead->SetPosition(this->x - KOOPAS_BBOX_WIDTH, this->y);
						_directionalHead->SetState(KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_LEFT);
					}
					else if (nx > 0)
					{
						SetState(KOOPAS_STATE_WALKING_RIGHT);
						SetFormation(KOOPAS_NORMAL_FORM);
						_directionalHead->SetPosition(this->x + KOOPAS_BBOX_WIDTH, this->y);
						_directionalHead->SetState(KOOPAS_DIRECTIONAL_HEAD_STATE_WALKING_RIGHT);
					}
				}
				else //GREEN
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
				}

				//mario->StopUntouchable();
				if (isHeld == 1 && mario->IsPressKeyA() == 1 && mario->GetHoldingState() == 1)
				{
					int level;
					mario->GetLevel(level);
					if (level == MARIO_LEVEL_HAVE_TAIL)
					{
						mario->SetLevel(MARIO_LEVEL_BIG);
						mario->StartUntouchable();
						mario->StartTransformationToHasWings();
					}
					else if (level == MARIO_LEVEL_BIG)
					{
						mario->SetLevel(MARIO_LEVEL_SMALL);
						mario->StartUntouchable();
						mario->StartTransformationToSmall();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						mario->SetState(MARIO_STATE_DIE);
					}
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

			int mario_level = 0;
			mario->GetLevel(mario_level);

			if (mario_level == MARIO_LEVEL_SMALL)
			{
				if (mario_nx >= 0)
				{
					x = mario_x + 10;
					y = mario_y - 2;
				}
				else
				{
					x = mario_x - 10;
					y = mario_y - 2;
				}
			}
			else
			{
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
		}
		else if (isHeld == 1 && mario->IsPressKeyA() == 0)
		{
			StopTickingTimeout();

			mario->StartUntouchable();
			mario->IsNoLongerActuallyHolding();
			mario->StartKicking();
			if (mario_nx >= 0)
				SetState(KOOPAS_STATE_SHELL_REVERSE_ROLL_RIGHT);
			else
				SetState(KOOPAS_STATE_SHELL_REVERSE_ROLL_LEFT);
		}
	}

	if (color == 0) //RED
	{
		//Directional head
		if (form == KOOPAS_NORMAL_FORM)
		{
			float directionalHead_x = 0, directionalHead_y = 0;
			_directionalHead->GetPosition(directionalHead_x, directionalHead_y);

			if (directionalHead_y - this->y >= KOOPAS_FALLEN_DISTANCE)
			{
				ChangeDirection();
			}
		}

		//Check activate of directional head
		if (form == KOOPAS_NORMAL_FORM)
			_directionalHead->IsActivate();
		else
			_directionalHead->IsNoActivate();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

	//Reset koopas shell reverse speed
	if (state == KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT || state == KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT)
	{
		if (isOnPlatform == 1)
			SetState(KOOPAS_STATE_SHELL_REVERSE_IDLE);
	}
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
		if (e->ny < 0) isOnPlatform = true;
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
	else if (dynamic_cast<CKoopas*>(e->obj) && form == KOOPAS_SHELL_FORM)
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CBrick*>(e->obj) && form == KOOPAS_SHELL_FORM)
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj) && form == KOOPAS_SHELL_FORM)
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CColorBox*>(e->obj) && form == KOOPAS_HAS_WINGS_FORM)
		OnCollisionWithColorBox(e);
	else if (dynamic_cast<CPlatform*>(e->obj) && form == KOOPAS_HAS_WINGS_FORM)
		OnCollisionWithPlatform(e);
}

void CKoopas::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
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

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if(nx != 0)
		e->obj->Delete();
}

void CKoopas::OnCollisionWithColorBox(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
		vy = -KOOPAS_DEFLECT_SPEED;
}

void CKoopas::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
		vy = -KOOPAS_DEFLECT_SPEED;
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


void CKoopas::Render()
{
	int aniId = -1;

	if (form == KOOPAS_HAS_WINGS_FORM)
	{
		if (state == KOOPAS_STATE_WALKING_LEFT)
		{
			aniId = ID_ANI_KOOPAS_GREEN_HAS_WINGS_WALKING_LEFT;
		}
		else if (state == KOOPAS_STATE_WALKING_RIGHT)
		{
			aniId = ID_ANI_KOOPAS_GREEN_HAS_WINGS_WALKING_RIGHT;
		}
	}
	else
	{
		if (color == 0) //RED
		{
			if (state == KOOPAS_STATE_WALKING_LEFT)
			{
				aniId = ID_ANI_KOOPAS_RED_WALKING_LEFT;
			}
			else if (state == KOOPAS_STATE_WALKING_RIGHT)
			{
				aniId = ID_ANI_KOOPAS_RED_WALKING_RIGHT;
			}
			else if (state == KOOPAS_STATE_SHELL_IDLE)
			{
				aniId = ID_ANI_KOOPAS_RED_SHELL_IDLE;
			}
			else if (state == KOOPAS_STATE_SHELL_ROLL_LEFT || state == KOOPAS_STATE_SHELL_ROLL_RIGHT)
			{
				aniId = ID_ANI_KOOPAS_RED_SHELL_ROLL;
			}
			else if (state == KOOPAS_STATE_SHELL_TIMEOUT)
			{
				aniId = ID_ANI_KOOPAS_RED_SHELL_TIMEOUT;
			}
			else if (state == KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT || state == KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT ||  state == KOOPAS_STATE_SHELL_REVERSE_IDLE)
			{
				aniId = ID_ANI_KOOPAS_RED_SHELL_REVERSE_IDLE;
			}
			else if (state == KOOPAS_STATE_SHELL_REVERSE_ROLL_LEFT || state == KOOPAS_STATE_SHELL_REVERSE_ROLL_RIGHT)
			{
				aniId = ID_ANI_KOOPAS_RED_SHELL_REVERSE_ROLL;
			}
			else if (state == KOOPAS_STATE_SHELL_REVERSE_TIMEOUT)
			{
				aniId = ID_ANI_KOOPAS_RED_SHELL_REVERSE_TIMEOUT;
			}
		}
		else if (color == 1) //GREEN
		{
			if (state == KOOPAS_STATE_WALKING_LEFT)
			{
				aniId = ID_ANI_KOOPAS_GREEN_WALKING_LEFT;
			}
			else if (state == KOOPAS_STATE_WALKING_RIGHT)
			{
				aniId = ID_ANI_KOOPAS_GREEN_WALKING_RIGHT;
			}
			else if (state == KOOPAS_STATE_SHELL_IDLE)
			{
				aniId = ID_ANI_KOOPAS_GREEN_SHELL_IDLE;
			}
			else if (state == KOOPAS_STATE_SHELL_ROLL_LEFT || state == KOOPAS_STATE_SHELL_ROLL_RIGHT)
			{
				aniId = ID_ANI_KOOPAS_GREEN_SHELL_ROLL;
			}
			else if (state == KOOPAS_STATE_SHELL_TIMEOUT)
			{
				aniId = ID_ANI_KOOPAS_GREEN_SHELL_TIMEOUT;
			}
			else if (state == KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT || state == KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT || state == KOOPAS_STATE_SHELL_REVERSE_IDLE)
			{
				aniId = ID_ANI_KOOPAS_GREEN_SHELL_REVERSE_IDLE;
			}
			else if (state == KOOPAS_STATE_SHELL_REVERSE_ROLL_LEFT || state == KOOPAS_STATE_SHELL_REVERSE_ROLL_RIGHT)
			{
				aniId = ID_ANI_KOOPAS_GREEN_SHELL_REVERSE_ROLL;
			}
			else if (state == KOOPAS_STATE_SHELL_REVERSE_TIMEOUT)
			{
				aniId = ID_ANI_KOOPAS_GREEN_SHELL_REVERSE_TIMEOUT;
			}
		}
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
	case KOOPAS_STATE_SHELL_REVERSE_IDLE:
		ay = 0;
		vy = 0;
		vx = 0;
		break;
	case KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT:
		vx = KOOPAS_BOUNCING_SPEED_X;
		vy = -KOOPAS_BOUNCING_SPEED_Y;
		break;
	case KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT:
		vx = -KOOPAS_BOUNCING_SPEED_X;
		vy = -KOOPAS_BOUNCING_SPEED_Y;
		break;
	case KOOPAS_STATE_SHELL_REVERSE_ROLL_LEFT:
		vx = -KOOPAS_ROLLING_SPEED;
		nx = -1;
		break;
	case KOOPAS_STATE_SHELL_REVERSE_ROLL_RIGHT:
		vx = KOOPAS_ROLLING_SPEED;
		nx = 1;
		break;
	case KOOPAS_STATE_SHELL_TIMEOUT:
		vx = 0;
		break;
	case KOOPAS_STATE_SHELL_REVERSE_TIMEOUT:
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
		y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_SHELL_BBOX_HEIGHT) / 2 + 1;
	}
	else if (this->form == KOOPAS_NORMAL_FORM)
	{
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_SHELL_BBOX_HEIGHT) / 2 - 1;
	}

	form = f;
}