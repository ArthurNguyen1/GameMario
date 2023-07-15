#include "Intro.h"

void CIntro::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_INTRO)->Render(x, y);

}