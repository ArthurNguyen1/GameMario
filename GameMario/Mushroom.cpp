#include "Mushroom.h"

#include "Goomba.h"
#include "QuestionBlock.h"
#include "Point.h"
#include "PlayScene.h"

#include "debug.h"

void CMushroom::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	float xx = 0, yy = 0;
	mario->GetPosition(xx, yy);

	e->src_obj->Delete();

	if (type == MUSHROOM_TYPE_NORMAL)
	{
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->StartTransformationToBig();

		CGameObject* obj = NULL;
		obj = new CPoint(xx, yy - 16, POINT_TYPE_1000);

		obj->SetPosition(xx, yy - 16);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
	}
	else
	{
		CGameObject* obj = NULL;
		obj = new CPoint(xx, yy - 16, POINT_TYPE_1UP);

		obj->SetPosition(xx, yy - 16);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
	}
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	else if (dynamic_cast<CMario*>(e->obj))
		OnCollisionWithMario(e);

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAlreadyMovedOutOfBlock == 1)
	{
		vy += ay * dt;
		vx += ax * dt;
	}
	else
	{
		if (y <= y_end)
		{
			y = y_end;
			isAlreadyMovedOutOfBlock = 1;
			vy = 0;

			srand((uint32_t)time(NULL));
			int rd = rand() % (1 - 0 + 1) + 0;
			if(rd == 0)
				vx = MUSHROOM_SPEED_X;
			else
				vx = -MUSHROOM_SPEED_X;

		}
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if(type == MUSHROOM_TYPE_NORMAL)
		animations->Get(ID_ANI_MUSHROOM)->Render(x, y);
	else
		animations->Get(ID_ANI_MUSHROOM_UP_HEART)->Render(x, y);
	
	RenderBoundingBox();
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}