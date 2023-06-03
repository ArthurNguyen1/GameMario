#include "ColorBox.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

int CColorBox::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}

void CColorBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CColorBox::RenderBoundingBox()
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

void CColorBox::Render()
{
	if (this->length <= 0) return;
	if (this->height <= 0) return;

	float xx = x;
	float yy = y;

	CSprites* s = CSprites::GetInstance();

	//Vẽ viền trên colorbox
	s->Get(this->spriteIdLeftTop)->Draw(xx, yy);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddleTop)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (length > 1)
		s->Get(this->spriteIdRightTop)->Draw(xx, yy);

	//Vẽ viền phải colorbox
	yy += this->cellHeight;
	for (int i = 1; i < this->height - 1; i++)
	{
		s->Get(this->spriteIdRightMid)->Draw(xx, yy);
		yy += this->cellHeight;
	}
	if ( (height > 1) && (length > 1) )
		s->Get(this->spriteIdRightBot)->Draw(xx, yy);

	//Set up lại về tọa độ điểm trái trên cùng (left,top)
	xx = x;
	yy = y;

	//Vẽ viền trái colorbox
	yy += this->cellHeight;
	for (int i = 1; i < this->height - 1; i++)
	{
		s->Get(this->spriteIdLeftMid)->Draw(xx, yy);
		yy += this->cellHeight;
	}
	if (height > 1)
		s->Get(this->spriteIdLeftBot)->Draw(xx, yy);

	//Vẽ viền dưới colorbox
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddleBot)->Draw(xx, yy);
		xx += this->cellWidth;
	}

	//Set up lại lần nữa
	xx = x + this->cellWidth;

	//Vẽ phần thân
	for (int i = 1; i < this->length - 1; i++)
	{
		yy = y + this->cellHeight;

		for (int j = 1; j < this->height - 1; j++)
		{
			s->Get(this->spriteIdMiddleMid)->Draw(xx, yy);
			yy += this->cellHeight;
		}

		xx += this->cellWidth;
	}

	RenderBoundingBox();
}

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2 + 4;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->length - 4;
	b = t + this->cellHeight;
}
