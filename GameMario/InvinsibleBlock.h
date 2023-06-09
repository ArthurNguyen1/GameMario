#pragma once

#include "GameObject.h"

#include "AssetIDs.h"

#define INVINSIBLE_BLOCK_TYPE_BLOCK_MARIO 0
#define INVINSIBLE_BLOCK_TYPE_CREATE_GOOMBA 2
#define INVINSIBLE_BLOCK_TYPE_CREATE_KOOPAS_HAS_WINGS 3
#define INVINSIBLE_BLOCK_TYPE_CREATE_KOOPAS_NORMAL 4


class CInvinsibleBlock : public CGameObject
{
protected:
	int length;				// Unit: cell 
	int height;
	float cellWidth;
	float cellHeight;

	int type;
	BOOLEAN isCreated; //0: no; 1: yes

public:
	CInvinsibleBlock(float x, float y, int length, int height, int type) :CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
		this->cellWidth = 16;
		this->cellHeight = 16;
		this->type = type;
		isCreated = 0;

		ObjectType = OBJECT_TYPE_INVINSIBLE_BLOCK;
	}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	
	int IsCollidable() { return 1; };
	int IsBlocking() { return this->type == INVINSIBLE_BLOCK_TYPE_BLOCK_MARIO; }

	int GetType() { return this->type; }

	BOOLEAN IsCreated() { return this->isCreated; }
	void IsAlreadyCreated() { this->isCreated = 1; }
};