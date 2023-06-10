#include "PiranhaPlant.h"

#include "PlayScene.h"

#include "Bullet.h"

CPiranhaPlant::CPiranhaPlant(float x, float y, BOOLEAN PlantColor, BOOLEAN CanShootFire) :CGameObject(x, y)
{
	this->PlantColor = PlantColor;
	this->CanShootFire = CanShootFire;
	this->isActivate = 0;

	y_start = y + 10;
	y_end = y - 33;

	this->vy = -PIRANHA_PLANT_SPEED_Y;
	isTickingAtTop = isTickingToShoot = isTickingAtBot = 0;
	time_at_top_start = time_at_bot_start = time_shooting_start = -1;
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHA_PLANT_BBOX_WIDTH / 2;
	top = y - PIRANHA_PLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHA_PLANT_BBOX_WIDTH;
	bottom = top + PIRANHA_PLANT_BBOX_HEIGHT;
}


void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);

	if (abs(this->x - mario_x) <= 120)
	{
		if (abs(this->x - mario_x) < 120 && abs(this->x - mario_x) >= 84)
		{
			if (this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 >= mario_x)
			{
				state = PIRANHA_PLANT_STATE_LEFT;
			}
			else
			{
				state = PIRANHA_PLANT_STATE_RIGHT;
			}

			y += vy * dt;
			isActivate = 1;

			if (y <= y_end)
			{
				y = y_end;

				if (isTickingAtTop == 0 && isTickingToShoot == 0)
				{
					time_at_top_start = time_shooting_start = GetTickCount64();
					isTickingAtTop = 1;
					isTickingToShoot = 1;
				}

				if (GetTickCount64() - time_shooting_start > PIRANHA_SHOOTING_TIME && isTickingToShoot == 1)
				{
					if (this->CanShootFire == 1)
					{
						if (this->state == PIRANHA_PLANT_STATE_LEFT)
						{
							CGameObject* obj = NULL;

							if (mario_y < this->y_end)
							{
								obj = new CBullet(this->x - 1, this->y, BULLET_STATE_LEFT_UP);
							}
							else if (this->y_end <= mario_y)
							{
								obj = new CBullet(this->x - 1, this->y, BULLET_STATE_LEFT_DOWN);
							}

							obj->SetPosition(x, y);
							((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);

							time_shooting_start = -1;
							isTickingToShoot = 0;
						}
						else
						{
							CGameObject* obj = NULL;

							if (mario_y < this->y_end)
							{
								obj = new CBullet(this->x + 1, this->y, BULLET_STATE_RIGHT_UP);
							}
							else if (this->y_end <= mario_y)
							{
								obj = new CBullet(this->x + 1, this->y, BULLET_STATE_RIGHT_DOWN);
							}

							obj->SetPosition(x, y);
							((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);

							time_shooting_start = -1;
							isTickingToShoot = 0;
						}

					}
				}

				if (GetTickCount64() - time_at_top_start > PIRANHA_AT_TOP_TIME && isTickingAtTop == 1)
				{
					vy = PIRANHA_PLANT_SPEED_Y;
					time_at_top_start = time_shooting_start = -1;
					isTickingAtTop = 0;
				}
				else
				{
					vy = 0.0f;
				}
			}
			if (y >= y_start)
			{
				y = y_start;

				if (isTickingAtBot == 0)
				{
					time_at_bot_start = GetTickCount64();
					isTickingAtBot = 1;
				}

				if (GetTickCount64() - time_at_bot_start > PIRANHA_AT_BOT_TIME && isTickingAtBot == 1)
				{
					vy = -PIRANHA_PLANT_SPEED_Y;
					time_at_bot_start = -1;
					isTickingAtBot = 0;
				}
				else
				{
					vy = 0.0f;
				}
			}
		}
		else if (abs(this->x - mario_x) < 84 && abs(this->x - mario_x) >= 30)
		{
			if (this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 >= mario_x)
			{
				state = PIRANHA_PLANT_STATE_LEFT;
			}
			else
			{
				state = PIRANHA_PLANT_STATE_RIGHT;
			}

			y += vy * dt;
			isActivate = 1;

			if (y <= y_end)
			{
				y = y_end;

				if (isTickingAtTop == 0 && isTickingToShoot == 0)
				{
					time_at_top_start = time_shooting_start = GetTickCount64();
					isTickingAtTop = 1;
					isTickingToShoot = 1;
				}

				if (GetTickCount64() - time_shooting_start > PIRANHA_SHOOTING_TIME && isTickingToShoot == 1)
				{
					if (this->CanShootFire == 1)
					{
						if (this->state == PIRANHA_PLANT_STATE_LEFT)
						{
							CGameObject* obj = NULL;

							if (mario_y < this->y_end - 30)
							{
								obj = new CBullet(this->x - 1, this->y, BULLET_STATE_LEFT_UP_HIGH);
							}
							else if (this->y_end - 30 <= mario_y && mario_y < this->y_end)
							{
								obj = new CBullet(this->x - 1, this->y, BULLET_STATE_LEFT_UP);
							}
							else if (this->y_end <= mario_y && mario_y < this->y_end + 20)
							{
								obj = new CBullet(this->x - 1, this->y, BULLET_STATE_LEFT_DOWN);
							}
							else if (this->y_end + 20 <= mario_y)
							{
								obj = new CBullet(this->x - 1, this->y, BULLET_STATE_LEFT_DOWN_LOW);
							}

							obj->SetPosition(x, y);
							((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);

							time_shooting_start = -1;
							isTickingToShoot = 0;
						}
						else
						{
							CGameObject* obj = NULL;

							if (mario_y < this->y_end - 30)
							{
								obj = new CBullet(this->x + 1, this->y, BULLET_STATE_RIGHT_UP_HIGH);
							}
							else if (this->y_end - 30 <= mario_y && mario_y < this->y_end)
							{
								obj = new CBullet(this->x + 1, this->y, BULLET_STATE_RIGHT_UP);
							}
							else if (this->y_end <= mario_y && mario_y < this->y_end + 20)
							{
								obj = new CBullet(this->x + 1, this->y, BULLET_STATE_RIGHT_DOWN);
							}
							else if (this->y_end + 20 <= mario_y)
							{
								obj = new CBullet(this->x + 1, this->y, BULLET_STATE_RIGHT_DOWN_LOW);
							}

							obj->SetPosition(x, y);
							((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);

							time_shooting_start = -1;
							isTickingToShoot = 0;
						}

					}
				}

				if (GetTickCount64() - time_at_top_start > PIRANHA_AT_TOP_TIME && isTickingAtTop == 1)
				{
					vy = PIRANHA_PLANT_SPEED_Y;
					time_at_top_start = time_shooting_start = -1;
					isTickingAtTop = 0;
				}
				else
				{
					vy = 0.0f;
				}
			}
			if (y >= y_start)
			{
				y = y_start;

				if (isTickingAtBot == 0)
				{
					time_at_bot_start = GetTickCount64();
					isTickingAtBot = 1;
				}

				if (GetTickCount64() - time_at_bot_start > PIRANHA_AT_BOT_TIME && isTickingAtBot == 1)
				{
					vy = -PIRANHA_PLANT_SPEED_Y;
					time_at_bot_start = -1;
					isTickingAtBot = 0;
				}
				else
				{
					vy = 0.0f;
				}
			}
		}

		else if (abs(this->x - mario_x) < 30) //this condition prevents the plant moving out of the pipe when mario is standing above it
		{
			if (this->GetActivateState() == 1 && y < y_start)
			{
				if (this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 >= mario_x)
				{
					state = PIRANHA_PLANT_STATE_LEFT;
				}
				else
				{
					state = PIRANHA_PLANT_STATE_RIGHT;
				}

				y += vy * dt;
				isActivate = 1;

				if (y <= y_end)
				{
					y = y_end;

					if (isTickingToShoot == 0 && isTickingAtTop == 0)
					{
						time_shooting_start = time_at_top_start = GetTickCount64();
						isTickingAtTop = 1;
						isTickingToShoot = 1;
					}

					if (GetTickCount64() - time_shooting_start > PIRANHA_SHOOTING_TIME && isTickingToShoot == 1)
					{
						if (this->CanShootFire == 1)
						{
							if (this->state == PIRANHA_PLANT_STATE_LEFT)
							{
								CGameObject* obj = NULL;

								if (mario_y < this->y_end)
								{
									obj = new CBullet(this->x - 1, this->y, BULLET_STATE_LEFT_UP_HIGH);
								}
								else if (this->y_end <= mario_y)
								{
									obj = new CBullet(this->x - 1, this->y, BULLET_STATE_LEFT_DOWN_LOW);
								}

								obj->SetPosition(x, y);
								((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);

								time_shooting_start = -1;
								isTickingToShoot = 0;

							}
							else
							{
								CGameObject* obj = NULL;

								if (mario_y < this->y_end)
								{
									obj = new CBullet(this->x + 1, this->y, BULLET_STATE_RIGHT_UP_HIGH);
								}
								else if (this->y_end <= mario_y)
								{
									obj = new CBullet(this->x + 1, this->y, BULLET_STATE_RIGHT_DOWN_LOW);
								}

								obj->SetPosition(x, y);
								((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);

								time_shooting_start = -1;
								isTickingToShoot = 0;
							}

						}
					}

					if (GetTickCount64() - time_at_top_start > PIRANHA_AT_TOP_TIME && isTickingAtTop == 1)
					{
						vy = PIRANHA_PLANT_SPEED_Y;
						time_at_top_start = -1;
						isTickingAtTop = 0;
					}
					else
					{
						vy = 0.0f;
					}
				}
			}
			else
			{
				y = y_start;
				isActivate = 0;
				this->vy = -PIRANHA_PLANT_SPEED_Y;
			}

		}		
	}
	else
	{
		if (y < y_start)
		{
			if (this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 >= mario_x)
			{
				state = PIRANHA_PLANT_STATE_LEFT;
			}
			else
			{
				state = PIRANHA_PLANT_STATE_RIGHT;
			}

			y += vy * dt;
			isActivate = 1;

			if (y <= y_end)
			{
				y = y_end;

				if (isTickingAtTop == 0)
				{
					time_at_top_start = GetTickCount64();
					isTickingAtTop = 1;
				}

				if (GetTickCount64() - time_at_top_start > PIRANHA_AT_TOP_TIME && isTickingAtTop == 1)
				{
					vy = PIRANHA_PLANT_SPEED_Y;
					time_at_top_start = -1;
					isTickingAtTop = 0;
				}
				else
				{
					vy = 0.0f;
				}
			}
		}
		else
		{
			y = y_start;
			isActivate = 0;
			this->vy = -PIRANHA_PLANT_SPEED_Y;
			time_at_bot_start = -1;
		}
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPiranhaPlant::Render()
{
	int aniId = this->GetAniId();
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

int CPiranhaPlant::GetAniId()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);

	int aniId = ID_ANI_PIRANHA_PLANT_RED_LEFT_DOWN;

	if (isActivate == 0)
	{
		return aniId;
	}
	else
	{
		if (PlantColor == 0)
		{
			if (this->y_end <= mario_y && this->x + PIRANHA_PLANT_BBOX_WIDTH/2 >= mario_x)
			{
				aniId = ID_ANI_PIRANHA_PLANT_RED_LEFT_DOWN;
			}
			if (mario_y < this->y_end && this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 >= mario_x)
			{
				aniId = ID_ANI_PIRANHA_PLANT_RED_LEFT_UP;
			}

			if (this->y_end <= mario_y && this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 < mario_x)
			{
				aniId = ID_ANI_PIRANHA_PLANT_RED_RIGHT_DOWN;
			}
			if (mario_y < this->y_end && this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 < mario_x)
			{
				aniId = ID_ANI_PIRANHA_PLANT_RED_RIGHT_UP;
			}
		}
		else
		{
			if (CanShootFire == 1)
			{
				if (this->y_end <= mario_y && this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 >= mario_x)
				{
					aniId = ID_ANI_PIRANHA_PLANT_GREEN_LEFT_DOWN;
				}
				if (mario_y < this->y_end && this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 >= mario_x)
				{
					aniId = ID_ANI_PIRANHA_PLANT_GREEN_LEFT_UP;
				}

				if (this->y_end <= mario_y && this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 < mario_x)
				{
					aniId = ID_ANI_PIRANHA_PLANT_GREEN_RIGHT_DOWN;
				}
				if (mario_y < this->y_end && this->x + PIRANHA_PLANT_BBOX_WIDTH / 2 < mario_x)
				{
					aniId = ID_ANI_PIRANHA_PLANT_GREEN_RIGHT_UP;
				}
			}
			else
				aniId = ID_ANI_PIRANHA_PLANT_GREEN_NO_SHOOT;
		}
	}

	return aniId;

}




