#include "QuestionBlock.h"
#include "debug.h"

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == QUESTION_BLOCK_STATE_WITH_ITEM) 
	{

	}
	else if (state == QUESTION_BLOCK_STATE_EMPTY)
	{
		if (IsMoving == true)
		{
			y += vy * dt;
			if (y <= y_end)
			{
				vy = -vy;
				y = y_end;
			}
			else if (y >= y_start)
			{
				IsMoving = false;
				y = y_start;
			}
		}
		else
		{
			y = y_start;
			vy = 0;
		}
		
	}
	CGameObject::Update(dt, coObjects);

}

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (IsMoving == false && state == QUESTION_BLOCK_STATE_WITH_ITEM)
	{
		animations->Get(ID_ANI_QUESTION_BLOCK_WITH_ITEM)->Render(x, y);
	}
	else
	{
		animations->Get(ID_ANI_QUESTION_BLOCK_EMPTY)->Render(x, y);
	}
	RenderBoundingBox();
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BLOCK_BBOX_WIDTH / 2;
	t = y - QUESTION_BLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTION_BLOCK_BBOX_WIDTH;
	b = t + QUESTION_BLOCK_BBOX_HEIGHT;
}