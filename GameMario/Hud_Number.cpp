#include "Hud_Number.h"

#include "PlayScene.h"

void CHud_Number::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cam_x = 0, cam_y = 0;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	if (this->type == CHUD_TYPE_NUMBER_WORLD)
	{
		this->x = cam_x + 60;
		this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_HEART)
	{
		this->x = cam_x + 60;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_COIN)
	{
		this->x = cam_x + 216;
		this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_TIME_POSITION_1)
	{
		this->x = cam_x + 216;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_TIME_POSITION_2)
	{
		this->x = cam_x + 204;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_TIME_POSITION_3)
	{
		this->x = cam_x + 192;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POINT_POSITION_1)
	{
		this->x = cam_x + 156;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POINT_POSITION_2)
	{
		this->x = cam_x + 144;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POINT_POSITION_3)
	{
		this->x = cam_x + 132;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POINT_POSITION_4)
	{
		this->x = cam_x + 120;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POINT_POSITION_5)
	{
		this->x = cam_x + 108;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POINT_POSITION_6)
	{
		this->x = cam_x + 96;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POINT_POSITION_7)
	{
		this->x = cam_x + 84;
		this->y = cam_y + 307;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_1)
	{
		this->x = cam_x + 162;
		this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_2)
	{
		this->x = cam_x + 144;
		this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_3)
	{
		this->x = cam_x + 132;
		this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_4)
	{
		this->x = cam_x + 120;
		this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_5)
	{
		this->x = cam_x + 108;
		this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_6)
	{
		this->x = cam_x + 96;
		this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_7)
	{
		this->x = cam_x + 84;
		this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_1)
	{
	this->x = cam_x + 162;
	this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_2)
	{
	this->x = cam_x + 144;
	this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_3)
	{
	this->x = cam_x + 132;
	this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_4)
	{
	this->x = cam_x + 120;
	this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_5)
	{
	this->x = cam_x + 108;
	this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_6)
	{
	this->x = cam_x + 96;
	this->y = cam_y + 295;
	}
	else if (this->type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_7)
	{
	this->x = cam_x + 84;
	this->y = cam_y + 295;
	}
}

void CHud_Number::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if(type == CHUD_TYPE_NUMBER_WORLD)
		animations->Get(ID_ANI_NUMBER_ONE)->Render(x, y);
	else if(type == CHUD_TYPE_NUMBER_HEART)
		animations->Get(ID_ANI_NUMBER_FOUR)->Render(x, y);
	else if (type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_2 || type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_3 || type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_4 || type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_5 || type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_6 || type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_7)
		animations->Get(ID_ANI_BLACK_SPEED)->Render(x, y);
	else if(type == CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_1)
		animations->Get(ID_ANI_BLACK_SPEED_POWER)->Render(x, y);
	else if (type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_2 || type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_3 || type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_4 || type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_5 || type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_6 || type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_7)
		animations->Get(ID_ANI_WHITE_SPEED)->Render(x, y);
	else if (type == CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_1)
		animations->Get(ID_ANI_WHITE_SPEED_POWER)->Render(x, y);
	else
		animations->Get(ID_ANI_NUMBER_ZERO)->Render(x, y);
}