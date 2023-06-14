#pragma once

#include "GameObject.h"


class CInvinsibleBlock : public CGameObject
{
protected:
	int length;				// Unit: cell 
	int height;
	float cellWidth;
	float cellHeight;

	BOOLEAN type; //0: Block koopas normal form; 1: Blockeverything

public:
	CInvinsibleBlock(float x, float y, int length, int height, BOOLEAN type) :CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
		this->cellWidth = 16;
		this->cellHeight = 16;
		this->type = type;
	}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	
	int IsCollidable() { return 1; };
	int IsBlocking() { return this->type; }
};