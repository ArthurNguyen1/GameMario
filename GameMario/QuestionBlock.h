#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTION_BLOCK_WITH_ITEM 10000
#define ID_ANI_QUESTION_BLOCK_EMPTY 10001

#define QUESTION_BLOCK_WIDTH 16
#define QUESTION_BLOCK_BBOX_WIDTH 16
#define QUESTION_BLOCK_BBOX_HEIGHT 16

#define QUESTION_BLOCK_STATE_WITH_ITEM 2
#define QUESTION_BLOCK_STATE_EMPTY	3

#define QUESTION_BLOCK_SPEED_Y 0.03f

class CQuestionBlock : public CGameObject {
private:
	BOOLEAN IsMoving;
	float y_start;
	float y_end;
public:
	CQuestionBlock(float x, float y) : CGameObject(x, y) 
	{ 
		IsMoving = false; 
		state = QUESTION_BLOCK_STATE_WITH_ITEM; 
		y_start = y;
		y_end = y - 20;
		vy = -QUESTION_BLOCK_SPEED_Y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetMovingState(BOOLEAN value) { this->IsMoving = value; }
};