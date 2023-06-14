#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_ROLLING_SPEED 0.07f


#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_SHELL_BBOX_WIDTH 16
#define KOOPAS_SHELL_BBOX_HEIGHT 16

#define KOOPAS_SHELL_START_TIMEOUT 4500
#define KOOPAS_SHELL_TIMEOUT 5000

#define KOOPAS_STATE_SHELL_IDLE			1400
#define KOOPAS_STATE_SHELL_ROLL_LEFT	1401
#define KOOPAS_STATE_SHELL_ROLL_RIGHT	1402
#define KOOPAS_STATE_SHELL_TIMEOUT		1403
#define KOOPAS_STATE_SHELL_REVERSE_IDLE				1410
#define KOOPAS_STATE_SHELL_REVERSE_ROLL_LEFT		1411
#define KOOPAS_STATE_SHELL_REVERSE_ROLL_RIGHT		1412
#define KOOPAS_STATE_SHELL_REVERSE_TIMEOUT			1413
#define KOOPAS_STATE_WALKING_LEFT	1420
#define KOOPAS_STATE_WALKING_RIGHT	1430

#define ID_ANI_KOOPAS_WALKING_LEFT	17001
#define ID_ANI_KOOPAS_WALKING_RIGHT	17000
#define ID_ANI_KOOPAS_SHELL_IDLE	17002
#define ID_ANI_KOOPAS_SHELL_ROLL	17003
#define ID_ANI_KOOPAS_SHELL_TIMEOUT	17004
#define ID_ANI_KOOPAS_SHELL_REVERSE_IDLE	17012
#define ID_ANI_KOOPAS_SHELL_REVERSE_ROLL	17013
#define ID_ANI_KOOPAS_SHELL_REVERSE_TIMEOUT	17014

#define KOOPAS_SHELL_FORM	0
#define KOOPAS_NORMAL_FORM	1

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	int form; //0: shell; 1: normal

	BOOLEAN isTimeout;
	ULONGLONG shell_start_timeout;

	void OnCollisionWithInvinsibleBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);


public:
	CKoopas(float x, float y);
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

	void StartTickingTimeout() { isTimeout= 1; shell_start_timeout = GetTickCount64(); }
	void StopTickingTimeout() { isTimeout = 0; shell_start_timeout = -1; }

};