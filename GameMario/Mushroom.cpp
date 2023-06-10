#include "Mushroom.h"

#include "Goomba.h"
#include "QuestionBlock.h"
#include "PlayScene.h"

#include "debug.h"

void CMushroom::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	mario->SetLevel(MARIO_LEVEL_BIG);

	e->src_obj->Delete();
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
			vx = MUSHROOM_SPEED_X;
			vy = 0;
		}
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_MUSHROOM)->Render(x, y);
	
	RenderBoundingBox();
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}