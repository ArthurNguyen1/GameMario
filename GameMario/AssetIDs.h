#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_TILESET 30
#define ID_TEX_MISC_2 40
#define ID_TEX_ENEMIES_RIGHT_TO_LEFT 50
#define ID_TEX_ENEMIES_LEFT_TO_RIGHT 60
#define	ID_TEX_PARTICLES 70
#define ID_TEX_MISC_2_REVERSE 80
#define ID_TEX_MARIO_LEFT_TO_RIGHT	90
#define ID_TEX_MARIO_RIGHT_TO_LEFT	100



#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_QUESTION_BLOCK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_GRASS 6
#define OBJECT_TYPE_CLOUD_BACKGROUND 7
#define OBJECT_TYPE_COLORBOX 8
#define OBJECT_TYPE_PIPE 9
#define OBJECT_TYPE_BRICK 10
#define OBJECT_TYPE_PIRANHA_PLANT 11
#define OBJECT_TYPE_BULLET	12
#define OBJECT_TYPE_MUSHROOM	13
#define OBJECT_TYPE_LEAF	14


#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#pragma endregion 

#pragma region QUESTION_BLOCK
#define ID_SPRITE_QUESTION_BLOCK 20000
#pragma endregion

#pragma region GOOMBA
#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)
#pragma endregion

#pragma region KOOPAS
#define ID_SPRITE_KOOPAS 160000
#pragma endregion

#pragma region COIN
//#define ID_SPRITE_COIN 40000
#define ID_SPRITE_COIN 130000
#pragma endregion

#pragma region PLATFORM
#define ID_SPRITE_PLATFORM 50000
#define ID_SPRITE_PLATFORM_BEGIN (ID_SPRITE_PLATFORM+1000)
#define ID_SPRITE_PLATFORM_MIDDLE (ID_SPRITE_PLATFORM+2000)
#define ID_SPRITE_PLATFORM_END (ID_SPRITE_PLATFORM+3000)
#define ID_SPRITE_PLATFORM_LOWER_BEGIN (ID_SPRITE_PLATFORM+4000)
#define ID_SPRITE_PLATFORM_LOWER_MIDDLE (ID_SPRITE_PLATFORM+5000)
#define ID_SPRITE_PLATFORM_LOWER_END (ID_SPRITE_PLATFORM+6000)
#pragma endregion

#pragma region GRASS
#define ID_SPRITE_GRASS 60000
#define ID_SPRITE_HUGE_GRASS_TOP_LEFT (ID_SPRITE_GRASS+1000)
#define ID_SPRITE_HUGE_GRASS_TOP_RIGHT (ID_SPRITE_GRASS+2000)
#define ID_SPRITE_HUGE_GRASS_MIDDLE_LEFT (ID_SPRITE_GRASS+3000)
#define ID_SPRITE_HUGE_GRASS_MIDDLE_RIGHT (ID_SPRITE_GRASS+4000)
#define ID_SPRITE_GRASS_MIDDLE (ID_SPRITE_GRASS+5000)
#define ID_SPRITE_SMALL_GRASS_TOP_LEFT (ID_SPRITE_GRASS+6000)
#define ID_SPRITE_SMALL_GRASS_TOP_RIGHT (ID_SPRITE_GRASS+7000)
#define ID_SPRITE_BUSH (ID_SPRITE_GRASS+8000)
#pragma endregion

#pragma region CLOUD
#define ID_SPRITE_CLOUD_BACKGROUND 70000
#define ID_SPRITE_CLOUD_BACKGROUND_BEGIN_TOP (ID_SPRITE_CLOUD_BACKGROUND+1000)
#define ID_SPRITE_CLOUD_BACKGROUND_BEGIN_BOT (ID_SPRITE_CLOUD_BACKGROUND+2000)
#define ID_SPRITE_CLOUD_BACKGROUND_MIDDLE_TOP (ID_SPRITE_CLOUD_BACKGROUND+3000)
#define ID_SPRITE_CLOUD_BACKGROUND_MIDDLE_BOT (ID_SPRITE_CLOUD_BACKGROUND+4000)
#define ID_SPRITE_CLOUD_BACKGROUND_END_TOP (ID_SPRITE_CLOUD_BACKGROUND+5000)
#define ID_SPRITE_CLOUD_BACKGROUND_END_BOT (ID_SPRITE_CLOUD_BACKGROUND+6000)
#pragma endregion

#pragma region COLORBOX 
#define ID_SPRITE_COLORBOX 80000
#define ID_SPRITE_COLORBOX_PINK_LEFT_TOP (ID_SPRITE_COLORBOX+1)
#define ID_SPRITE_COLORBOX_PINK_LEFT_MID (ID_SPRITE_COLORBOX+2)
#define ID_SPRITE_COLORBOX_PINK_LEFT_BOT (ID_SPRITE_COLORBOX+3)
#define ID_SPRITE_COLORBOX_PINK_MIDDLE_TOP (ID_SPRITE_COLORBOX+4)
#define ID_SPRITE_COLORBOX_PINK_MIDDLE_MID (ID_SPRITE_COLORBOX+5)
#define ID_SPRITE_COLORBOX_PINK_MIDDLE_BOT (ID_SPRITE_COLORBOX+6)
#define ID_SPRITE_COLORBOX_PINK_RIGHT_TOP (ID_SPRITE_COLORBOX+7)
#define ID_SPRITE_COLORBOX_PINK_RIGHT_MID (ID_SPRITE_COLORBOX+8)
#define ID_SPRITE_COLORBOX_PINK_RIGHT_BOT (ID_SPRITE_COLORBOX+9)

#define ID_SPRITE_COLORBOX_BLUE_LEFT_TOP (ID_SPRITE_COLORBOX+11)
#define ID_SPRITE_COLORBOX_BLUE_LEFT_MID (ID_SPRITE_COLORBOX+12)
#define ID_SPRITE_COLORBOX_BLUE_LEFT_BOT (ID_SPRITE_COLORBOX+13)
#define ID_SPRITE_COLORBOX_BLUE_MIDDLE_TOP (ID_SPRITE_COLORBOX+14)
#define ID_SPRITE_COLORBOX_BLUE_MIDDLE_MID (ID_SPRITE_COLORBOX+15)
#define ID_SPRITE_COLORBOX_BLUE_MIDDLE_BOT (ID_SPRITE_COLORBOX+16)
#define ID_SPRITE_COLORBOX_BLUE_RIGHT_TOP (ID_SPRITE_COLORBOX+17)
#define ID_SPRITE_COLORBOX_BLUE_RIGHT_MID (ID_SPRITE_COLORBOX+18)
#define ID_SPRITE_COLORBOX_BLUE_RIGHT_BOT (ID_SPRITE_COLORBOX+19)

#define ID_SPRITE_COLORBOX_GREEN_LEFT_TOP (ID_SPRITE_COLORBOX+21)
#define ID_SPRITE_COLORBOX_GREEN_LEFT_MID (ID_SPRITE_COLORBOX+22)
#define ID_SPRITE_COLORBOX_GREEN_LEFT_BOT (ID_SPRITE_COLORBOX+23)
#define ID_SPRITE_COLORBOX_GREEN_MIDDLE_TOP (ID_SPRITE_COLORBOX+24)
#define ID_SPRITE_COLORBOX_GREEN_MIDDLE_MID (ID_SPRITE_COLORBOX+25)
#define ID_SPRITE_COLORBOX_GREEN_MIDDLE_BOT (ID_SPRITE_COLORBOX+26)
#define ID_SPRITE_COLORBOX_GREEN_RIGHT_TOP (ID_SPRITE_COLORBOX+27)
#define ID_SPRITE_COLORBOX_GREEN_RIGHT_MID (ID_SPRITE_COLORBOX+28)
#define ID_SPRITE_COLORBOX_GREEN_RIGHT_BOT (ID_SPRITE_COLORBOX+29)

#define ID_SPRITE_COLORBOX_WHITE_LEFT_TOP (ID_SPRITE_COLORBOX+31)
#define ID_SPRITE_COLORBOX_WHITE_LEFT_MID (ID_SPRITE_COLORBOX+32)
#define ID_SPRITE_COLORBOX_WHITE_LEFT_BOT (ID_SPRITE_COLORBOX+33)
#define ID_SPRITE_COLORBOX_WHITE_MIDDLE_TOP (ID_SPRITE_COLORBOX+34)
#define ID_SPRITE_COLORBOX_WHITE_MIDDLE_MID (ID_SPRITE_COLORBOX+35)
#define ID_SPRITE_COLORBOX_WHITE_MIDDLE_BOT (ID_SPRITE_COLORBOX+36)
#define ID_SPRITE_COLORBOX_WHITE_RIGHT_TOP (ID_SPRITE_COLORBOX+37)
#define ID_SPRITE_COLORBOX_WHITE_RIGHT_MID (ID_SPRITE_COLORBOX+38)
#define ID_SPRITE_COLORBOX_WHITE_RIGHT_BOT (ID_SPRITE_COLORBOX+39)

#define ID_SPRITE_COLORBOX_BLACK_LEFT_TOP (ID_SPRITE_COLORBOX+41)
#define ID_SPRITE_COLORBOX_BLACK_LEFT_MID (ID_SPRITE_COLORBOX+42)
#define ID_SPRITE_COLORBOX_BLACK_LEFT_BOT (ID_SPRITE_COLORBOX+43)
#define ID_SPRITE_COLORBOX_BLACK_MIDDLE_TOP (ID_SPRITE_COLORBOX+44)
#define ID_SPRITE_COLORBOX_BLACK_MIDDLE_MID (ID_SPRITE_COLORBOX+45)
#define ID_SPRITE_COLORBOX_BLACK_MIDDLE_BOT (ID_SPRITE_COLORBOX+46)
#define ID_SPRITE_COLORBOX_BLACK_RIGHT_TOP (ID_SPRITE_COLORBOX+47)
#define ID_SPRITE_COLORBOX_BLACK_RIGHT_MID (ID_SPRITE_COLORBOX+48)
#define ID_SPRITE_COLORBOX_BLACK_RIGHT_BOT (ID_SPRITE_COLORBOX+49)

#define ID_SPRITE_COLORBOX_SHADE_RIGHT_TOP (ID_SPRITE_COLORBOX+51)
#define ID_SPRITE_COLORBOX_SHADE_LEFT_BOT (ID_SPRITE_COLORBOX+52)
#define ID_SPRITE_COLORBOX_SHADE_MIDDLE (ID_SPRITE_COLORBOX+53)
#define ID_SPRITE_COLORBOX_SHADE_RIGHT_BOT (ID_SPRITE_COLORBOX+54)
#pragma endregion

#pragma region PIPE
#define ID_SPRITE_PIPE 90000
#define ID_SPRITE_PIPE_TOP_LEFT (ID_SPRITE_PIPE+1000)
#define ID_SPRITE_PIPE_TOP_RIGHT (ID_SPRITE_PIPE+2000)
#define ID_SPRITE_PIPE_BODY_LEFT (ID_SPRITE_PIPE+3000)
#define ID_SPRITE_PIPE_BODY_RIGHT (ID_SPRITE_PIPE+4000)
#pragma endregion

#pragma region BRICK
//#define ID_SPRITE_BRICK 100000
#pragma endregion

#pragma region PIRANHAPLANT
#define ID_SPRITE_PIRANHA_PLANT	110000
#define ID_SPRITE_PIRANHA_PLANT_RED_LEFT_DOWN_OPEN_MOUTH	(ID_SPRITE_PIRANHA_PLANT+1100)
#define ID_SPRITE_PIRANHA_PLANT_RED_LEFT_DOWN_CLOSE_MOUTH	(ID_SPRITE_PIRANHA_PLANT+1200)
#define ID_SPRITE_PIRANHA_PLANT_RED_LEFT_UP_OPEN_MOUTH		(ID_SPRITE_PIRANHA_PLANT+1300)
#define ID_SPRITE_PIRANHA_PLANT_RED_LEFT_UP_CLOSE_MOUTH		(ID_SPRITE_PIRANHA_PLANT+1400)
#define ID_SPRITE_PIRANHA_PLANT_RED_RIGHT_DOWN_OPEN_MOUTH	(ID_SPRITE_PIRANHA_PLANT+1600)
#define ID_SPRITE_PIRANHA_PLANT_RED_RIGHT_DOWN_CLOSE_MOUTH	(ID_SPRITE_PIRANHA_PLANT+1500)
#define ID_SPRITE_PIRANHA_PLANT_RED_RIGHT_UP_OPEN_MOUTH		(ID_SPRITE_PIRANHA_PLANT+1800)
#define ID_SPRITE_PIRANHA_PLANT_RED_RIGHT_UP_CLOSE_MOUTH	(ID_SPRITE_PIRANHA_PLANT+1700)

#define ID_SPRITE_PIRANHA_PLANT_GREEN_LEFT_DOWN_OPEN_MOUTH		(ID_SPRITE_PIRANHA_PLANT+2100)
#define ID_SPRITE_PIRANHA_PLANT_GREEN_LEFT_DOWN_CLOSE_MOUTH		(ID_SPRITE_PIRANHA_PLANT+2200)
#define ID_SPRITE_PIRANHA_PLANT_GREEN_LEFT_UP_OPEN_MOUTH		(ID_SPRITE_PIRANHA_PLANT+2300)
#define ID_SPRITE_PIRANHA_PLANT_GREEN_LEFT_UP_CLOSE_MOUTH		(ID_SPRITE_PIRANHA_PLANT+2400)
#define ID_SPRITE_PIRANHA_PLANT_GREEN_RIGHT_DOWN_OPEN_MOUTH		(ID_SPRITE_PIRANHA_PLANT+2600)
#define ID_SPRITE_PIRANHA_PLANT_GREEN_RIGHT_DOWN_CLOSE_MOUTH	(ID_SPRITE_PIRANHA_PLANT+2500)
#define ID_SPRITE_PIRANHA_PLANT_GREEN_RIGHT_UP_OPEN_MOUTH		(ID_SPRITE_PIRANHA_PLANT+2800)
#define ID_SPRITE_PIRANHA_PLANT_GREEN_RIGHT_UP_CLOSE_MOUTH		(ID_SPRITE_PIRANHA_PLANT+2700)

#define ID_SPRITE_PIRANHA_PLANT_GREEN_OPEN_MOUTH	(ID_SPRITE_PIRANHA_PLANT+3100)
#define ID_SPRITE_PIRANHA_PLANT_GREEN_CLOSE_MOUTH	(ID_SPRITE_PIRANHA_PLANT+3200)
#pragma endregion

#pragma region BULLET
#define ID_SPRITE_BULLET 120000
#pragma endregion

#pragma region MUSHROOM
#define ID_SPRITE_MUSHROOM	141000
#pragma endregion

#pragma region LEAF
#define ID_SPRITE_LEAF_RIGHT_TO_LEFT	151000
#define ID_SPRITE_LEAF_LEFT_TO_RIGHT	152000
#pragma endregion