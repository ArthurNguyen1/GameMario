#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_NUMBER_ZERO 22010
#define ID_ANI_NUMBER_ONE 22011
#define ID_ANI_NUMBER_TWO 22012
#define ID_ANI_NUMBER_THREE 22013
#define ID_ANI_NUMBER_FOUR 22014
#define ID_ANI_NUMBER_FIVE 22015
#define ID_ANI_NUMBER_SIX 22016
#define ID_ANI_NUMBER_SEVEN 22017
#define ID_ANI_NUMBER_EIGHT 22018
#define ID_ANI_NUMBER_NINE 22019

#define ID_ANI_WHITE_SPEED 22005
#define ID_ANI_WHITE_SPEED_POWER 22006
#define ID_ANI_BLACK_SPEED 22007
#define ID_ANI_BLACK_SPEED_POWER 22008


#define CHUD_TYPE_NUMBER_WORLD 0
#define CHUD_TYPE_NUMBER_HEART 1
#define CHUD_TYPE_NUMBER_COIN 2
#define CHUD_TYPE_NUMBER_TIME_POSITION_1 3
#define CHUD_TYPE_NUMBER_TIME_POSITION_2 4
#define CHUD_TYPE_NUMBER_TIME_POSITION_3 5
#define CHUD_TYPE_NUMBER_POINT_POSITION_1 11
#define CHUD_TYPE_NUMBER_POINT_POSITION_2 12
#define CHUD_TYPE_NUMBER_POINT_POSITION_3 13
#define CHUD_TYPE_NUMBER_POINT_POSITION_4 14
#define CHUD_TYPE_NUMBER_POINT_POSITION_5 15
#define CHUD_TYPE_NUMBER_POINT_POSITION_6 16
#define CHUD_TYPE_NUMBER_POINT_POSITION_7 17

#define CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_1 21
#define CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_2 22
#define CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_3 23
#define CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_4 24
#define CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_5 25
#define CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_6 26
#define CHUD_TYPE_NUMBER_POWER_BLACK_POSITION_7 27

#define CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_1 31
#define CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_2 32
#define CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_3 33
#define CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_4 34
#define CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_5 35
#define CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_6 36
#define CHUD_TYPE_NUMBER_POWER_WHITE_POSITION_7 37

class CHud_Number : public CGameObject {
private:
	int type;
public:
	CHud_Number(float x, float y, int type, int ObjectType) : CGameObject(x, y)
	{
		this->ObjectType = ObjectType;
		this->type = type;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
};
