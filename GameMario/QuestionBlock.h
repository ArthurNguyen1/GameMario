#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTION_BLOCK_WITH_ITEM 10000
#define ID_ANI_QUESTION_BLOCK_EMPTY 10001

#define QUESTION_BLOCK_WIDTH 16
#define QUESTION_BLOCK_BBOX_WIDTH 16
#define QUESTION_BLOCK_BBOX_HEIGHT 16

#define QUESTION_BLOCK_STATE_WITH_SPECIAL_ITEM 1102
#define QUESTION_BLOCK_STATE_WITH_COIN_ITEM 1101
#define QUESTION_BLOCK_STATE_EMPTY	1100

#define QUESTION_BLOCK_SPEED_Y 0.03f

class CQuestionBlock : public CGameObject {
private:
	BOOLEAN isMoving;
	float y_start;
	float y_end;
public:
	CQuestionBlock(float x, float y, int state) : CGameObject(x, y) 
	{ 
		isMoving = false; 
		this->state = state; 
		y_start = y;
		y_end = y - 20;
		vy = -QUESTION_BLOCK_SPEED_Y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 0; }
	void SetMovingState(BOOLEAN value) { this->isMoving = value; }
};