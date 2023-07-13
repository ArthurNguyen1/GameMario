#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "QuestionBlock.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Coin.h"

class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	
	void AddObject(LPGAMEOBJECT obj) { objects.push_back(obj); }
	void InsertObject(LPGAMEOBJECT obj) { objects.insert(objects.begin() + 198, obj); } //Insert right after mario
	void ActivateButton()
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->GetObjectType() == OBJECT_TYPE_BRICK_SHINE)
			{
				float xx = 0, yy = 0;
				objects[i]->GetPosition(xx, yy);

				CGameObject* obj = NULL;

				obj = new CCoin(xx, yy, 1);

				objects.push_back(obj);

				objects.erase(objects.begin() + i);
			}
		}
	}

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

