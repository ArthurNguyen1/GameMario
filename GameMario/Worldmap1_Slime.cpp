#include "Worldmap1_Slime.h"

void CWorldmap1_Slime::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_WORLDMAP_SLIME)->Render(x, y);
}