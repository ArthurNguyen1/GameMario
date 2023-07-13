#include "Button.h"

#include "PlayScene.h"

void CButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (isActivate == 0)
	{
		animations->Get(ID_ANI_BUTTON)->Render(x, y);
	}
	else
	{
		animations->Get(ID_ANI_BUTTON_DISABLE)->Render(x, y);
	}

	RenderBoundingBox();
}

void CButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isActivate == 0)
	{
		l = x - BUTTON_BBOX_WIDTH / 2;
		t = y - BUTTON_BBOX_HEIGHT / 2;
		r = l + BUTTON_BBOX_WIDTH;
		b = t + BUTTON_BBOX_HEIGHT;
	}
	else
	{
		l = x - BUTTON_BBOX_WIDTH / 2;
		t = y - BUTTON_DISABLE_BBOX_HEIGHT / 2;
		r = l + BUTTON_BBOX_WIDTH;
		b = t + BUTTON_DISABLE_BBOX_HEIGHT;
	}

	
}