#pragma once
#include "GameObject.h"
#include "KoopasDirectionalHead.h"

#define KOOPAS_GRAVITY 0.0006f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_ROLLING_SPEED 0.2f
#define KOOPAS_DEFLECT_SPEED  0.2f
#define KOOPAS_JUMPING_SPEED_Y 0.6f

#define KOOPAS_BOUNCING_SPEED_X 0.1f
#define KOOPAS_BOUNCING_SPEED_Y 0.24f


#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_SHELL_BBOX_WIDTH 16
#define KOOPAS_SHELL_BBOX_HEIGHT 16
#define KOOPAS_HAS_WINGS_BBOX_WIDTH 16
#define KOOPAS_HAS_WINGS_BBOX_HEIGHT 27

#define KOOPAS_SHELL_START_TIMEOUT 4500
#define KOOPAS_SHELL_TIMEOUT 5000

#define KOOPAS_STATE_SHELL_IDLE			1400
#define KOOPAS_STATE_SHELL_ROLL_LEFT	1401
#define KOOPAS_STATE_SHELL_ROLL_RIGHT	1402
#define KOOPAS_STATE_SHELL_TIMEOUT		1403
#define KOOPAS_STATE_SHELL_REVERSE_IDLE			1410
#define KOOPAS_STATE_SHELL_REVERSE_ROLL_LEFT		1411
#define KOOPAS_STATE_SHELL_REVERSE_ROLL_RIGHT		1412
#define KOOPAS_STATE_SHELL_REVERSE_TIMEOUT		1413
#define KOOPAS_STATE_SHELL_REVERSE_IDLE_LEFT		1414
#define KOOPAS_STATE_SHELL_REVERSE_IDLE_RIGHT		1415
#define KOOPAS_STATE_WALKING_LEFT	1420
#define KOOPAS_STATE_WALKING_RIGHT	1430

#define ID_ANI_KOOPAS_RED_WALKING_LEFT	17001
#define ID_ANI_KOOPAS_RED_WALKING_RIGHT	17000
#define ID_ANI_KOOPAS_RED_SHELL_IDLE	17002
#define ID_ANI_KOOPAS_RED_SHELL_ROLL	17003
#define ID_ANI_KOOPAS_RED_SHELL_TIMEOUT	17004
#define ID_ANI_KOOPAS_RED_SHELL_REVERSE_IDLE	17012
#define ID_ANI_KOOPAS_RED_SHELL_REVERSE_ROLL	17013
#define ID_ANI_KOOPAS_RED_SHELL_REVERSE_TIMEOUT	17014

#define ID_ANI_KOOPAS_GREEN_WALKING_LEFT	17021
#define ID_ANI_KOOPAS_GREEN_WALKING_RIGHT	17020
#define ID_ANI_KOOPAS_GREEN_SHELL_IDLE		17022
#define ID_ANI_KOOPAS_GREEN_SHELL_ROLL		17023
#define ID_ANI_KOOPAS_GREEN_SHELL_TIMEOUT	17024
#define ID_ANI_KOOPAS_GREEN_SHELL_REVERSE_IDLE		17042
#define ID_ANI_KOOPAS_GREEN_SHELL_REVERSE_ROLL		17043
#define ID_ANI_KOOPAS_GREEN_SHELL_REVERSE_TIMEOUT	17044

#define ID_ANI_KOOPAS_GREEN_HAS_WINGS_WALKING_LEFT	17031
#define ID_ANI_KOOPAS_GREEN_HAS_WINGS_WALKING_RIGHT	17030

#define KOOPAS_SHELL_FORM	0
#define KOOPAS_NORMAL_FORM	1
#define KOOPAS_HAS_WINGS_FORM	2


class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	
	int color; //0:red; 1:green

	int form; //0: shell; 1: normal; 2: has wings
	
	BOOLEAN isOnPlatform;

	BOOLEAN isTimeout;
	ULONGLONG shell_start_timeout;

	BOOLEAN isHeld;

	BOOLEAN isReverse;

	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithColorBox(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);

	CKoopasDirectionalHead* _directionalHead;

	void ChangeDirection();

public:
	CKoopas(float x, float y, int color, int form);
	void SetState(int state);
	void SetFormation(int f);
	int GetFormation() { return form; }

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void StartTickingTimeout() { isTimeout = 1; shell_start_timeout = GetTickCount64(); this->ay = 0; this->vy = 0; }
	void StopTickingTimeout() { isTimeout = 0; shell_start_timeout = -1; this->isHeld = 0; 	this->ay = KOOPAS_GRAVITY;}

	void StartTickingReverseTimeout() { isTimeout = 1; shell_start_timeout = GetTickCount64(); }


	void IsHeld() { this->isHeld = 1; }
	void IsNotHeld() { this->isHeld = 0; }

	void ResetDirectionalHead();

	void IsReverse() { isReverse = 1; }

	BOOLEAN GetReverseState() { return isReverse; }
};