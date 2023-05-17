#include "Pipe.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CPipe::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPipe::Render()
{
	if (this->height <= 0) return;
	float xx1 = x;
	float xx2 = x + this->cellWidth;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdTopLeft)->Draw(xx1, yy);
	s->Get(this->spriteIdTopRight)->Draw(xx2, yy);
	yy += this->cellHeight;
	for (int i = 1; i < this->height; i++)
	{
		s->Get(this->spriteIdBodyLeft)->Draw(xx1, yy);
		s->Get(this->spriteIdBodyRight)->Draw(xx2, yy);
		yy += this->cellHeight;
	}

	RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2 + 4;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * 2 - 4;
	b = t + this->cellHeight * this->height;
}

