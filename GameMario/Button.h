#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_BUTTON			20000
#define ID_ANI_BUTTON_DISABLE	20001

#define BUTTON_BBOX_WIDTH 15
#define BUTTON_BBOX_HEIGHT 15
#define BUTTON_DISABLE_BBOX_HEIGHT 6

class CButton : public CGameObject {
private:
	BOOLEAN isActivate;
public:
	CButton(float x, float y) : CGameObject(x, y)
	{
		isActivate = 0;
		ObjectType = OBJECT_TYPE_BUTTON;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }

	void IsActivate() { this->isActivate = 1; }
	BOOLEAN GetActivateState() { return this->isActivate; }
};