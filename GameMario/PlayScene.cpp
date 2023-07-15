#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Grass.h"
#include "CloudBackground.h"
#include "ColorBox.h"
#include "Pipe.h"
#include "PiranhaPlant.h"
#include "Bullet.h"
#include "Mushroom.h"
#include "Koopas.h"
#include "InvinsibleBlock.h"
#include "ItemBackground.h"
#include "GoalRoulette.h"
#include "Hud.h"
#include "Hud_RewardBox.h"
#include "Hud_Background.h"
#include "Hud_Number.h"
#include "Worldmap1_Background.h"
#include "Worldmap1_Slime.h"
#include "Worldmap1_Turtle.h"
#include "Intro.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		int level = atoi(tokens[3].c_str());
		int type = atoi(tokens[4].c_str());

		obj = new CMario(x, y, level, type);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OBJECT_TYPE_GOOMBA: 
	{
		BOOLEAN color = atoi(tokens[3].c_str());
		int level = atoi(tokens[4].c_str());

		obj = new CGoomba(x, y, color, level);

		break;
	}

	case OBJECT_TYPE_KOOPAS: 
	{
		int color = atoi(tokens[3].c_str());
		int form = atoi(tokens[4].c_str());
		obj = new CKoopas(x, y, color, form); 
		break;
	}

	case OBJECT_TYPE_WORLDMAP_BACKGROUND:
	{
		int aniId = atoi(tokens[3].c_str());

		obj = new CWorldmap1_Background(x, y, aniId);
		break;
	}
	case OBJECT_TYPE_WORLDMAP_SLIME:
	{
		obj = new CWorldmap1_Slime(x, y);
		break;
	}
	case OBJECT_TYPE_WORLDMAP_TURTLE:
	{
		obj = new CWorldmap1_Turtle(x, y);
		break;
	}
	case OBJECT_TYPE_SCREEN_INTRO:
	{
		obj = new CIntro(x, y);
		break;
	}

	case OBJECT_TYPE_HUD:
	{
		obj = new CHud(x, y);
		break;
	}
	case OBJECT_TYPE_HUD_REWARDBOX:
	{
		int numberbox = atoi(tokens[3].c_str());

		obj = new CHud_RewardBox(x, y, numberbox);
		break;
	}
	case OBJECT_TYPE_HUD_BACKGROUND:
	{
		int number = atoi(tokens[3].c_str());

		obj = new CHud_Background(x, y, number);
		break;
	}
	case OBJECT_TYPE_HUD_NUMBER_NORMAL:
	{
		int type = atoi(tokens[3].c_str());
		int Objecttype = atoi(tokens[4].c_str());

		obj = new CHud_Number(x, y, type, Objecttype);
		break;
	}

	case OBJECT_TYPE_QUESTION_BLOCK: 
	{
		BOOLEAN type = atoi(tokens[3].c_str());

		obj = new CQuestionBlock(x, y, type); 

		break; 
	}

	case OBJECT_TYPE_BRICK: 
	{
		int aniId = atoi(tokens[3].c_str());

		obj = new CBrick(x, y, aniId); 
		break;
	}
	case OBJECT_TYPE_COIN: 
	{
		BOOLEAN type = atoi(tokens[3].c_str());

		obj = new CCoin(x, y, type);
		break;
	}

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_COLORBOX:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());

		int sprite_left_top = atoi(tokens[7].c_str());
		int sprite_left_mid = atoi(tokens[8].c_str());
		int sprite_left_bot = atoi(tokens[9].c_str());

		int sprite_middle_top = atoi(tokens[10].c_str());
		int sprite_middle_mid = atoi(tokens[11].c_str());
		int sprite_middle_bot = atoi(tokens[12].c_str());

		int sprite_right_top = atoi(tokens[13].c_str());
		int sprite_right_mid = atoi(tokens[14].c_str());
		int sprite_right_bot = atoi(tokens[15].c_str());


		obj = new CColorBox(
			x, y,
			cell_width, cell_height, length, height,
			sprite_left_top, sprite_left_mid, sprite_left_bot,
			sprite_middle_top, sprite_middle_mid, sprite_middle_bot,
			sprite_right_top, sprite_right_mid, sprite_right_bot
		);

		break;
	}

	case OBJECT_TYPE_INVINSIBLE_BLOCK:
	{
		int length = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		int type = atoi(tokens[5].c_str());


		obj = new CInvinsibleBlock(x, y, length, height, type);
		break;
	}

	case OBJECT_TYPE_PIRANHA_PLANT:
	{
		BOOLEAN PlantColor = (BOOLEAN)atoi(tokens[3].c_str());
		BOOLEAN CanShootFire = (BOOLEAN)atoi(tokens[4].c_str()); 

		obj = new CPiranhaPlant(
			x, y,
			PlantColor, CanShootFire
		);

		break;
	}

	case OBJECT_TYPE_PIPE:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		int sprite_top_left = atoi(tokens[6].c_str());
		int sprite_top_right = atoi(tokens[7].c_str());
		int sprite_body_left = atoi(tokens[8].c_str());
		int sprite_body_right = atoi(tokens[9].c_str());


		obj = new CPipe(
			x, y,
			cell_width, cell_height, height,
			sprite_top_left, sprite_top_right, sprite_body_left, sprite_body_right
		);

		break;
	}

	case OBJECT_TYPE_CLOUD_BACKGROUND:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin_top = atoi(tokens[6].c_str());
		int sprite_begin_bot = atoi(tokens[7].c_str());
		int sprite_middle_top = atoi(tokens[8].c_str());
		int sprite_middle_bot = atoi(tokens[9].c_str());
		int sprite_end_top = atoi(tokens[10].c_str());
		int sprite_end_bot = atoi(tokens[11].c_str());


		obj = new CCloudBackground(
			x, y,
			cell_width, cell_height, length,
			sprite_begin_top, sprite_begin_bot,
			sprite_middle_top, sprite_middle_bot, 
			sprite_end_top, sprite_end_bot
		);

		break;
	}

	case OBJECT_TYPE_GRASS:
	{
		int sprite_id = atoi(tokens[3].c_str());

		obj = new CGrass(
			x, y, 
			sprite_id
		);

		break;
	}

	case OBJECT_TYPE_GOAL_ROULETTE:
	{
		int type = atoi(tokens[3].c_str());

		obj = new CGoalRoulette(x, y, type);
		break;
	}

	case OBJECT_TYPE_ITEM_BACKGROUND:
	{
		int sprite_id = atoi(tokens[3].c_str());

		obj = new CItemBackground(
			x, y,
			sprite_id
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}


	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;
	if (cy > 0) cy = 0;

	CMario* mario = (CMario*)player;
	if(mario->GetMarioType()==MARIO_TYPE_PLAYSCENE )
		CGame::GetInstance()->SetCamPos(cx, cy);
	else
	{
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
	}

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}