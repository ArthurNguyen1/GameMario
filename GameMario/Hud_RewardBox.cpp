#include "Hud_RewardBox.h"

#include "PlayScene.h"

void CHud_RewardBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cam_x = 0, cam_y = 0;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	if (this->boxnumber == POSITION_FIRST_BOX)
	{
		this->x = cam_x + 247;
		this->y = cam_y + 300;
	}
	else if (this->boxnumber == POSITION_SECOND_BOX)
	{
		this->x = cam_x + 283;
		this->y = cam_y + 300;
	}
	else if (this->boxnumber == POSITION_THIRD_BOX)
	{
		this->x = cam_x + 319;
		this->y = cam_y + 300;
	}

	/*CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);*/
}

void CHud_RewardBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_REWARD_BOX_EMPTY)->Render(x, y);
}