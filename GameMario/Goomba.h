#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f

#define GOOMBA_READY_TO_JUMP_SPEED_Y 0.1f
#define GOOMBA_JUMPING_SPEED_Y 0.4f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_HAS_WINGS_BBOX_WIDTH 18
#define GOOMBA_HAS_WINGS_BBOX_HEIGHT 20

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_WALKING_TIMEOUT 1000
#define GOOMBA_READY_TO_JUMP_TIMEOUT 500
#define GOOMBA_JUMPING_TIMEOUT 1000


#define GOOMBA_STATE_WALKING 101
#define GOOMBA_STATE_READY_TO_JUMP 102
#define GOOMBA_STATE_JUMPING 103
#define GOOMBA_STATE_DIE 201

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

#define ID_ANI_GOOMBA_RED_HAS_WINGS_WALKING 5002
#define ID_ANI_GOOMBA_RED_HAS_WINGS_JUMPING 5003
#define ID_ANI_GOOMBA_RED_HAS_NO_WINGS_WALKING 5004
#define ID_ANI_GOOMBA_RED_DIE 5005

#define GOOMBA_LEVEL_WALK 1
#define GOOMBA_LEVEL_JUMP 2

class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	BOOLEAN color; //0: no color, 1: red

	int level; //1: walk only, 2: jump (only red goomba can jump)

	BOOLEAN isWalking;
	ULONGLONG walking_start;
	BOOLEAN isReadyToJump1;
	ULONGLONG ready_to_jump_start1;
	BOOLEAN isReadyToJump2;
	ULONGLONG ready_to_jump_start2;
	BOOLEAN isReadyToJump3;
	ULONGLONG ready_to_jump_start3;
	BOOLEAN isJumping;
	ULONGLONG jumping_start;

public:
	CGoomba(float x, float y, BOOLEAN color, int level);
	virtual void SetState(int state);

	void StartWalking() { isWalking = 1; walking_start = GetTickCount64(); }
	void StopWalking() { isWalking = 0; walking_start = -1; }

	void StartReadyToJump1() { isReadyToJump1 = 1; ready_to_jump_start1 = GetTickCount64(); }
	void StopReadyToJump1() { isReadyToJump1 = 0; ready_to_jump_start1 = -1; }

	void StartReadyToJump2() { isReadyToJump2 = 1; ready_to_jump_start2 = GetTickCount64(); }
	void StopReadyToJump2() { isReadyToJump2 = 0; ready_to_jump_start2 = -1; }

	void StartReadyToJump3() { isReadyToJump3 = 1; ready_to_jump_start3 = GetTickCount64(); }
	void StopReadyToJump3() { isReadyToJump3 = 0; ready_to_jump_start3 = -1; }

	void StartJumping() { isJumping = 1; jumping_start = GetTickCount64(); }
	void StopJumping() { isJumping = 0; jumping_start = -1; }

	void SetLevel(int level);
	int GetLevel() { return this->level; }


	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

};