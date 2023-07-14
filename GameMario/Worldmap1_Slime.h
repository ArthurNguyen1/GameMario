#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_WORLDMAP_SLIME 23001

class CWorldmap1_Slime : public CGameObject {
public:
	CWorldmap1_Slime(float x, float y) : CGameObject(x, y)
	{
		ObjectType = OBJECT_TYPE_WORLDMAP_SLIME;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
};


