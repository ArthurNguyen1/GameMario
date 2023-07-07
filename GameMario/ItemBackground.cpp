#include "ItemBackground.h"

void CItemBackground::Render()
{
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteId)->Draw(x, y);
}