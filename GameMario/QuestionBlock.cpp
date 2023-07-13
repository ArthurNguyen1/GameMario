#include "QuestionBlock.h"

#include "PlayScene.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Button.h"
#include "debug.h"

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	int mario_level;
	mario->GetLevel(mario_level);

	if (state == QUESTION_BLOCK_STATE_WITH_ITEM) 
	{

	}
	else if (state == QUESTION_BLOCK_STATE_EMPTY)
	{
		if (isMoving == 1)
		{
			y += vy * dt;
			if (y <= y_end)
			{
				vy = -vy;
				y = y_end;
			}
			else if (y >= y_start)
			{
				isMoving = 0;
				y = y_start;

				if (mario_level == MARIO_LEVEL_SMALL && type == QUESTION_BLOCK_TYPE_SPECIAL_ITEM)
				{
					CGameObject* obj = NULL;

					obj = new CMushroom(x, y - 1, MUSHROOM_TYPE_NORMAL);

					obj->SetPosition(x, y - 1);
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->InsertObject(obj);
				}
				else if (mario_level >= MARIO_LEVEL_BIG && type == QUESTION_BLOCK_TYPE_SPECIAL_ITEM)
				{
					CGameObject* obj = NULL;

					obj = new CLeaf(x, y - 8);

					obj->SetPosition(x, y - 8);
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
				}
				else if (type == QUESTION_BLOCK_TYPE_UP_HEART)
				{
					CGameObject* obj = NULL;

					obj = new CMushroom(x, y - 1, MUSHROOM_TYPE_UP_HEART);

					obj->SetPosition(x, y - 1);
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->InsertObject(obj);
				}
			}
		}
		else
		{
			y = y_start;
			vy = 0;

			if(type == QUESTION_BLOCK_TYPE_BUTTON)
			{
				CGameObject* obj = NULL;

				obj = new CButton(x, y - 16);

				obj->SetPosition(x, y - 16);
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
			}
		}
		
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (isMoving == false && state == QUESTION_BLOCK_STATE_WITH_ITEM)
	{
		if (type == QUESTION_BLOCK_TYPE_UP_HEART || type == QUESTION_BLOCK_TYPE_BUTTON)
		{
			animations->Get(ID_ANI_QUESTION_BLOCK_WITH_ITEM_SHINE)->Render(x, y);
		}
		else
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