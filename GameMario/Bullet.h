#pragma once
#include "GameObject.h"

#define BULLET_SPEED_X 0.04f
#define BULLET_SPEED_Y 0.01f

#define BULLET_BBOX_WIDTH 8
#define BULLET_BBOX_HEIGHT 9

#define BULLET_STATE_LEFT_UP_HIGH	1301
#define BULLET_STATE_LEFT_UP		1302
#define BULLET_STATE_LEFT_DOWN		1303
#define BULLET_STATE_LEFT_DOWN_LOW	1304

#define BULLET_STATE_RIGHT_UP_HIGH	1305	
#define BULLET_STATE_RIGHT_UP		1306	
#define BULLET_STATE_RIGHT_DOWN		1307	
#define BULLET_STATE_RIGHT_DOWN_LOW	1308	


#define ID_ANI_BULLET_LEFT 13001
#define ID_ANI_BULLET_RIGHT 13002

class CBullet : public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CBullet(float x, float y, int state);
};