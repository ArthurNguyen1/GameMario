#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_REWARD_BOX_EMPTY		22001
#define ID_ANI_REWARD_BOX_MUSHROOM	22002
#define ID_ANI_REWARD_BOX_PLANT		22003
#define ID_ANI_REWARD_BOX_STAR		22004

#define POSITION_FIRST_BOX	1
#define POSITION_SECOND_BOX	2
#define POSITION_THIRD_BOX	3

class CHud_RewardBox : public CGameObject {
private:
	int boxnumber;
public:
	CHud_RewardBox(float x, float y, int numberbox) : CGameObject(x, y)
	{
		ObjectType = OBJECT_TYPE_HUD_REWARDBOX;

		float cam_x = 0, cam_y = 0;
		CGame::GetInstance()->GetCamPos(cam_x, cam_y);

		this->boxnumber = numberbox;

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
		
		
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
};