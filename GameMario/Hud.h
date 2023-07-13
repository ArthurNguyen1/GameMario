#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_INFO_BAR			22000

class CHud : public CGameObject {
public:
	CHud(float x, float y) : CGameObject(x, y)
	{
		ObjectType = OBJECT_TYPE_HUD;

		float cam_x = 0, cam_y = 0;
		CGame::GetInstance()->GetCamPos(cam_x, cam_y);

		this->x = cam_x + 115;
		this->y = cam_y + 300;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
};