#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_DARK_BACKGROUND		22050

#define POSITION_ONE	1
#define POSITION_TWO	2
#define POSITION_THREE	3
#define POSITION_FOUR	4
#define POSITION_FIVE	5
#define POSITION_SIX	6

class CHud_Background : public CGameObject {
private:
	int position_number;
public:
	CHud_Background(float x, float y, int number) : CGameObject(x, y)
	{
		ObjectType = OBJECT_TYPE_HUD_BACKGROUND;

		float cam_x = 0, cam_y = 0;
		CGame::GetInstance()->GetCamPos(cam_x, cam_y);

		this->position_number = number;

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


	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
};
