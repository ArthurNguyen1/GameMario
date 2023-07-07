#include "GoalRoulette.h"

#include "PlayScene.h"

void CGoalRoulette::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
}

void CGoalRoulette::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (type == TYPE_GOAL_ROULETTE_BACKGROUND)
		animations->Get(ID_ANI_GOAL_ROULETTE_BACKGROUND)->Render(x, y);
	else if(type == TYPE_GOAL_ROULETTE_ITEM_BACKGROUND)
		animations->Get(ID_ANI_GOAL_ROULETTE_ITEM_BACKGROUND)->Render(x, y);
	else
		animations->Get(ID_ANI_GOAL_REWARD)->Render(x, y);

	RenderBoundingBox();
}

void CGoalRoulette::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (type == TYPE_GOAL_REWARD)
	{
		l = x - GOAL_REWARD_BBOX_WIDTH / 2;
		t = y - GOAL_REWARD_BBOX_HEIGHT / 2;
		r = l + GOAL_REWARD_BBOX_WIDTH;
		b = t + GOAL_REWARD_BBOX_HEIGHT;
	}
}