#include "Worldmap1_Background.h"

void CWorldmap1_Background::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(aniId)->Render(x, y);
}