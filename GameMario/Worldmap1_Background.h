#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "AssetIDs.h"

#define ID_ANI_WORLDMAP_BACKGROUND 23000
#define ID_ANI_WORLDMAP_CROSSLINE_VERTICAL 23032
#define ID_ANI_WORLDMAP_CROSSLINE_HORIZONTAL 23033

#define ID_ANI_WORLDMAP_ROAD_HORIZONTAL 23022
#define ID_ANI_WORLDMAP_ROAD_VERTICAL 23023
#define ID_ANI_WORLDMAP_ROAD_HORIZONTAL_WITH_NODE 23024
#define ID_ANI_WORLDMAP_ROAD_VERTICAL_WITH_NODE 23025
#define ID_ANI_WORLDMAP_START 23005

#define ID_ANI_WORLDMAP_NODE_1 23011

class CWorldmap1_Background : public CGameObject {
private:
	int aniId;
public:
	CWorldmap1_Background(float x, float y, int aniID) : CGameObject(x, y)
	{
		this->aniId = aniID;
		ObjectType = OBJECT_TYPE_WORLDMAP_BACKGROUND;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
};


