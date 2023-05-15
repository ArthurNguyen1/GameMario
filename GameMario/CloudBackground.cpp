#include "CloudBackground.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CCloudBackground::Render()
{
	if (this->length <= 0) return;
	float xx = x;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdBeginTop)->Draw(xx, y);
	s->Get(this->spriteIdBeginBot)->Draw(xx, y + this->cellHeight);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddleTop)->Draw(xx, y);
		s->Get(this->spriteIdMiddleBot)->Draw(xx, y + this->cellHeight);
		xx += this->cellWidth;
	}
	if (length > 1)
	{
		s->Get(this->spriteIdEndTop)->Draw(xx, y);
		s->Get(this->spriteIdEndBot)->Draw(xx, y + this->cellHeight);
	}

	RenderBoundingBox();
}

