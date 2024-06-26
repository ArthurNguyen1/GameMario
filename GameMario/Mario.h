#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "Tail.h"
#include "debug.h"

#define MARIO_WORLDMAP_SPEED_X		1.5f
#define MARIO_WORLDMAP_SPEED_Y		1.5f

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.22f

#define MARIO_ACCEL_WALK_X	0.0002f
#define MARIO_ACCEL_RUN_X	0.00022f

#define MARIO_JUMP_SPEED_Y		0.3f
#define MARIO_JUMP_RUN_SPEED_Y	0.32f

#define MARIO_GRAVITY			0.0006f


#define MARIO_FLYING_SPEED_X		0.12f
#define MARIO_FLYING_FAST_SPEED_X	0.2f
#define MARIO_FLYING_SPEED_Y		0.2f

#define MARIO_ACCEL_FLY_X		0.0002f
#define MARIO_ACCEL_FLY_FAST_X	0.00022f
#define MARIO_ACCEL_FLY_Y	0.0002f


#define MARIO_JUMP_DEFLECT_SPEED  0.2f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_HITTING			20

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICKING_RIGHT	700
#define MARIO_STATE_KICKING_LEFT	701

#define MARIO_STATE_HOLDING			800
#define MARIO_STATE_HOLDING_RELEASE	801

#define MARIO_STATE_FLYING_RIGHT	900
#define MARIO_STATE_FLYING_LEFT		901
#define MARIO_STATE_FLYING_FAST_RIGHT	902
#define MARIO_STATE_FLYING_FAST_LEFT	903
#define MARIO_STATE_FLYING_IDLE		904
#define MARIO_STATE_FLYABLE_FALLING_RIGHT	905
#define MARIO_STATE_FLYABLE_FALLING_LEFT	906
#define MARIO_STATE_FLYABLE_FALLING_IDLE	907

#define MARIO_STATE_FALLING_SLOW_RIGHT	910
#define MARIO_STATE_FALLING_SLOW_LEFT	911
#define MARIO_STATE_FALLING_FAST_RIGHT	912
#define MARIO_STATE_FALLING_FAST_LEFT	913
#define MARIO_STATE_FALLING_SLOW_IDLE	914
#define MARIO_STATE_FALLING_FAST_IDLE	915

#define MARIO_STATE_TRANSFORMATION_SMALL_TO_BIG		916
#define MARIO_STATE_TRANSFORMATION_BIG_TO_SMALL		917
#define MARIO_STATE_TRANSFORMATION_TO_HAS_WINGS		918

#define MARIO_STATE_WORLDMAP_GO_LEFT 951
#define MARIO_STATE_WORLDMAP_GO_RIGHT 952
#define MARIO_STATE_WORLDMAP_GO_UP 953
#define MARIO_STATE_WORLDMAP_GO_DOWN 954
#define MARIO_STATE_WORLDMAP_IDLE 955


#pragma region ANIMATION_ID
#define ID_ANI_MARIO_WORLDMAP 3750

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_KICKING_RIGHT 1700
#define ID_ANI_MARIO_KICKING_LEFT 1701

#define ID_ANI_MARIO_HOLDING_SHELL_IDLE_RIGHT 2700
#define ID_ANI_MARIO_HOLDING_SHELL_IDLE_LEFT 2701

#define ID_ANI_MARIO_HOLDING_SHELL_WALKING_RIGHT 2800
#define ID_ANI_MARIO_HOLDING_SHELL_WALKING_LEFT 2801

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_TRANSFORMATION_FROM_SMALL_TO_BIG_RIGHT	951
#define ID_ANI_MARIO_TRANSFORMATION_FROM_SMALL_TO_BIG_LEFT	952
#define ID_ANI_MARIO_TRANSFORMATION_FROM_BIG_TO_SMALL_RIGHT	953
#define ID_ANI_MARIO_TRANSFORMATION_FROM_BIG_TO_SMALL_LEFT	954
#define ID_ANI_MARIO_TRANSFORMATION_TO_HAS_WINGS	950

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICKING_RIGHT 1800
#define ID_ANI_MARIO_SMALL_KICKING_LEFT 1801

#define ID_ANI_MARIO_SMALL_HOLDING_SHELL_IDLE_RIGHT 2900
#define ID_ANI_MARIO_SMALL_HOLDING_SHELL_IDLE_LEFT 2902

#define ID_ANI_MARIO_SMALL_HOLDING_SHELL_WALKING_RIGHT 3000
#define ID_ANI_MARIO_SMALL_HOLDING_SHELL_WALKING_LEFT 3001

// MARIO HAVE TAIL
#define ID_ANI_MARIO_HAVE_TAIL_IDLE_RIGHT 1900
#define ID_ANI_MARIO_HAVE_TAIL_IDLE_LEFT 1902

#define ID_ANI_MARIO_HAVE_TAIL_WALKING_RIGHT 2000
#define ID_ANI_MARIO_HAVE_TAIL_WALKING_LEFT 2001

#define ID_ANI_MARIO_HAVE_TAIL_RUNNING_RIGHT 2100
#define ID_ANI_MARIO_HAVE_TAIL_RUNNING_LEFT 2101

#define ID_ANI_MARIO_HAVE_TAIL_BRACE_RIGHT 2200
#define ID_ANI_MARIO_HAVE_TAIL_BRACE_LEFT 2201

#define ID_ANI_MARIO_HAVE_TAIL_JUMP_WALK_RIGHT 2300
#define ID_ANI_MARIO_HAVE_TAIL_JUMP_WALK_LEFT 2301

#define ID_ANI_MARIO_HAVE_TAIL_JUMP_RUN_RIGHT 2400
#define ID_ANI_MARIO_HAVE_TAIL_JUMP_RUN_LEFT 2401

#define ID_ANI_MARIO_HAVE_TAIL_KICKING_RIGHT 2500
#define ID_ANI_MARIO_HAVE_TAIL_KICKING_LEFT 2501

#define ID_ANI_MARIO_HAVE_TAIL_SIT_RIGHT 2600
#define ID_ANI_MARIO_HAVE_TAIL_SIT_LEFT 2601

#define ID_ANI_MARIO_HAVE_TAIL_HOLDING_SHELL_IDLE_RIGHT 3100
#define ID_ANI_MARIO_HAVE_TAIL_HOLDING_SHELL_IDLE_LEFT 3102

#define ID_ANI_MARIO_HAVE_TAIL_HOLDING_SHELL_WALKING_RIGHT 3200
#define ID_ANI_MARIO_HAVE_TAIL_HOLDING_SHELL_WALKING_LEFT 3201

#define ID_ANI_MARIO_HAVE_TAIL_FLYING_RIGHT 3300
#define ID_ANI_MARIO_HAVE_TAIL_FLYING_LEFT 3301

#define ID_ANI_MARIO_HAVE_TAIL_FLYABLE_FALLING_RIGHT 3400
#define ID_ANI_MARIO_HAVE_TAIL_FLYABLE_FALLING_LEFT 3401

#define ID_ANI_MARIO_HAVE_TAIL_FALLING_SLOW_RIGHT 3500
#define ID_ANI_MARIO_HAVE_TAIL_FALLING_SLOW_LEFT 3501

#define ID_ANI_MARIO_HAVE_TAIL_FALLING_FAST_RIGHT 3600
#define ID_ANI_MARIO_HAVE_TAIL_FALLING_FAST_LEFT 3601

#define ID_ANI_MARIO_HAVE_TAIL_HITTING_RIGHT 3700
#define ID_ANI_MARIO_HAVE_TAIL_HITTING_LEFT 3701
#pragma endregion

#define GROUND_Y 160.0f


#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_HAVE_TAIL	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 14

#define MARIO_HAVE_TAIL_BBOX_WIDTH  16
#define MARIO_HAVE_TAIL_BBOX_HEIGHT 26
#define MARIO_HAVE_TAIL_SITTING_BBOX_WIDTH  15
#define MARIO_HAVE_TAIL_SITTING_BBOX_HEIGHT 18

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICKING_TIME 250
#define MARIO_HITTING_TIME 200
#define MARIO_TRANSFORMATION_TIME 600

#define MARIO_FLYABLE_TIME 27500
#define MARIO_SET_FLY_STATE_TIME 58500

#define MARIO_SET_FALL_STATE_TIME 200000

#define MARIO_TYPE_WOLRDMAP 0
#define MARIO_TYPE_PLAYSCENE 1
#define MARIO_TYPE_INTRO 2

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float maxVy;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	CTail* _tail;

	int level;
	int type; //1:Mario in playscene, 0:Mario in WorldMap

	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin;

	BOOLEAN isKicking;
	ULONGLONG kicking_start;

	BOOLEAN isPressKeyA;
	BOOLEAN isHolding;

	BOOLEAN isHitting;
	ULONGLONG hitting_start;

	ULONGLONG press_key_A_running_start; //Counting time that set state as running
	ULONGLONG release_key_A_stop_running_start; //Counting time when release state running

	LONGLONG total_time_press_key_A_running; //total time when set and release state running, this use to identify fly condition

	BOOLEAN isCountingTimeToFly; //is it start counting to fly or not

	BOOLEAN canFly;

	BOOLEAN isFlying;
	ULONGLONG flying_start;
	LONGLONG total_time_to_fly;

	BOOLEAN isFalling; //this variable used to know when the time flying is over
	BOOLEAN isCountingFalling; //this variable use to set the falling_start once
	ULONGLONG falling_start;
	LONGLONG total_time_to_fall;

	BOOLEAN isTransformationToBig;
	ULONGLONG transformation_to_big_start;

	BOOLEAN isTransformationToSmall;
	ULONGLONG transformation_to_small_start;

	BOOLEAN isTransformationToHasWings;
	ULONGLONG transformation_to_has_wings_start;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithNode(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithButton(LPCOLLISIONEVENT e);
	void OnCollisionWithInvinsibleBlock(LPCOLLISIONEVENT e);


	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdHaveTail();

public:
	CMario(float x, float y, int level, int type);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetLevel(int& level) { level = this->level; }
	void SetLevel(int next_level);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StopUntouchable() { untouchable = 0; untouchable_start = -1; }
	
	void StartKicking() { isKicking = true; kicking_start = GetTickCount64(); }
	void StopKicking() { isKicking = false; kicking_start = -1; }

	void StartHitting() {  hitting_start = GetTickCount64(); }
	void StopHitting() { hitting_start = -1; }


	void StartTransformationToBig() { isTransformationToBig = true; transformation_to_big_start = GetTickCount64(); }
	void StopTransformationToBig() { isTransformationToBig = false; transformation_to_big_start = -1; }

	void StartTransformationToSmall() { isTransformationToSmall = true; transformation_to_small_start = GetTickCount64(); }
	void StopTransformationToSmall() { isTransformationToSmall = false; transformation_to_small_start = -1; }

	void StartTransformationToHasWings() { isTransformationToHasWings = true; transformation_to_has_wings_start = GetTickCount64(); }
	void StopTransformationToHasWings() { isTransformationToHasWings = false; transformation_to_has_wings_start = -1; }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	BOOLEAN IsPressKeyA() { return this->isPressKeyA; }
	void StartPressingKeyA() { press_key_A_running_start = GetTickCount64(); }
	void StopPressingKeyA() { release_key_A_stop_running_start = GetTickCount64(); }

	BOOLEAN GetFlyableState() { return canFly; }
	void StartFlying() { total_time_to_fly = MARIO_SET_FLY_STATE_TIME ; flying_start = GetTickCount64(); }

	BOOLEAN IsFlying() { return isFlying; }
	BOOLEAN IsFalling() { return isFalling; }
	void StartFalling() { total_time_to_fall = MARIO_SET_FALL_STATE_TIME; falling_start = GetTickCount64(); }
	void StopFalling() { total_time_to_fall = 0; falling_start = -1; }

	BOOLEAN GetHoldingState() { return this->isHolding; }
	void IsNoLongerActuallyHolding() { this->isHolding = false; }

	int GetMarioType() { return this->type; }
};