#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_INTRO	24000

class CIntro : public CGameObject {
public:
	CIntro(float x, float y) : CGameObject(x, y)
	{
		ObjectType = OBJECT_TYPE_SCREEN_INTRO;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; };
};

