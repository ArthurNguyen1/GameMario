#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_HOLDING);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_HAVE_TAIL);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_HOLDING_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	int level;
	mario->GetLevel(level);

	if (game->IsKeyDown(DIK_X))
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (mario->IsFalling() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FALLING_SLOW_RIGHT);
			else if (mario->GetFlyableState() == true && level == MARIO_LEVEL_HAVE_TAIL)
			{
				if (game->IsKeyDown(DIK_A))
					mario->SetState(MARIO_STATE_FLYING_FAST_RIGHT);
				else
					mario->SetState(MARIO_STATE_FLYING_RIGHT);
			}
			else
				mario->SetState(MARIO_STATE_FALLING_FAST_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (mario->IsFalling() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FALLING_SLOW_LEFT);
			else if (mario->GetFlyableState() == true && level == MARIO_LEVEL_HAVE_TAIL)
			{
				if (game->IsKeyDown(DIK_A))
					mario->SetState(MARIO_STATE_FLYING_FAST_LEFT);
				else
					mario->SetState(MARIO_STATE_FLYING_LEFT);
			}
			else
				mario->SetState(MARIO_STATE_FALLING_FAST_LEFT);
		}
		else
		{
			if (mario->IsFalling() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FALLING_SLOW_IDLE);
			else if (mario->GetFlyableState() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FLYING_IDLE);
			else
				mario->SetState(MARIO_STATE_IDLE);
		}
	}
	else
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (mario->IsFalling() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FALLING_FAST_RIGHT);
			else if (mario->IsFlying() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FLYABLE_FALLING_RIGHT);
			else if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (mario->IsFalling() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FALLING_FAST_LEFT);
			else if (mario->IsFlying() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FLYABLE_FALLING_LEFT);
			else if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
		{
			if (mario->IsFalling() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FALLING_FAST_IDLE);
			else if (mario->IsFlying() == true && level == MARIO_LEVEL_HAVE_TAIL)
				mario->SetState(MARIO_STATE_FLYABLE_FALLING_IDLE);
			else
				mario->SetState(MARIO_STATE_IDLE);
		}
	}
}