#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

//#define ID_ANI_COIN 11000
#define ID_ANI_COIN_SMALL	14000
#define ID_ANI_COIN_BIG		14001

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 8
#define COIN_BBOX_HEIGHT 14

#define COIN_SPEED_Y 0.1f

class CCoin : public CGameObject {
private:
	BOOLEAN type; //0: small; 1:big
	float y_start;
	float y_end;
public:
	CCoin(float x, float y, BOOLEAN type) : CGameObject(x, y) 
	{ 
		this->type = type; 
		y_start = y;
		y_end = y - 40;

		vy = -COIN_SPEED_Y;

		ObjectType = OBJECT_TYPE_COIN;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return this->type; };

	
	bool GetType() { return this->type; }
};