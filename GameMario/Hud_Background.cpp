#include "Hud_Background.h"

#include "PlayScene.h"

void CHud_Background::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cam_x = 0, cam_y = 0;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	if (this->position_number == POSITION_ONE)
	{
		this->x = cam_x + 30;
		this->y = cam_y + 358;
	}
	else if (this->position_number == POSITION_TWO)
	{
		this->x = cam_x + 100;
		this->y = cam_y + 358;
	}
	else if (this->position_number == POSITION_THREE)
	{
		this->x = cam_x + 170;
		this->y = cam_y + 358;
	}
	else if (this->position_number == POSITION_FOUR)
	{
		this->x = cam_x + 240;
		this->y = cam_y + 358;
	}
	else if (this->position_number == POSITION_FIVE)
	{
		this->x = cam_x + 310;
		this->y = cam_y + 358;
	}

	/*CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);*/
}

void CHud_Background::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_DARK_BACKGROUND)->Render(x, y);
}