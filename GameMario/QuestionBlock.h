#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTION_BLOCK_WITH_ITEM 10000
#define ID_ANI_QUESTION_BLOCK_EMPTY 10001
#define ID_ANI_QUESTION_BLOCK_WITH_ITEM_SHINE 18001

#define QUESTION_BLOCK_WIDTH 16
#define QUESTION_BLOCK_BBOX_WIDTH 16
#define QUESTION_BLOCK_BBOX_HEIGHT 16

#define QUESTION_BLOCK_STATE_WITH_ITEM 1101
#define QUESTION_BLOCK_STATE_EMPTY	1100

#define QUESTION_BLOCK_SPEED_Y 0.04f

#define QUESTION_BLOCK_TYPE_COIN 0
#define QUESTION_BLOCK_TYPE_SPECIAL_ITEM 1
#define QUESTION_BLOCK_TYPE_UP_HEART 2

class CQuestionBlock : public CGameObject {
private:
	BOOLEAN isMoving;
	float y_start;
	float y_end;
	int type; //0: coin; 1: special item (mushroom/leaf); 2: mushroom up heart
public:
	CQuestionBlock(float x, float y, int type) : CGameObject(x, y) 
	{ 
		isMoving = 0; 
		this->state = QUESTION_BLOCK_STATE_WITH_ITEM;
		y_start = y;
		y_end = y - 10;
		vy = -QUESTION_BLOCK_SPEED_Y;
		this->type = type;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 0; }

	void SetMovingState(BOOLEAN value) { this->isMoving = value; }
	int GetType() { return this->type; }
};