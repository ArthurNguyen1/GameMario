#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_GOAL_ROULETTE_BACKGROUND			21000
#define ID_ANI_GOAL_ROULETTE_ITEM_BACKGROUND	21001
#define ID_ANI_GOAL_REWARD	21002

#define GOAL_REWARD_BBOX_WIDTH 25
#define GOAL_REWARD_BBOX_HEIGHT 25

#define TYPE_GOAL_ROULETTE_BACKGROUND	1
#define TYPE_GOAL_ROULETTE_ITEM_BACKGROUND	2
#define TYPE_GOAL_REWARD	3

//#define COIN_SPEED_Y 0.1f

class CGoalRoulette : public CGameObject {
private:
	int type;
	/*float y_start;
	float y_end;*/
public:
	CGoalRoulette(float x, float y, int type) : CGameObject(x, y)
	{
		this->type = type;
		/*y_start = y;
		y_end = y - 40;*/

		//vy = -COIN_SPEED_Y;

		ObjectType = OBJECT_TYPE_GOAL_ROULETTE;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return this->type == TYPE_GOAL_REWARD; };
};