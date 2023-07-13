#include "Hud.h"

#include "PlayScene.h"

void CHud::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cam_x = 0, cam_y = 0;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	x = cam_x + 115;
	y = cam_y + 300;

	/*CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);*/
}

void CHud::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_INFO_BAR)->Render(x, y);
}