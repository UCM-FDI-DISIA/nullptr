
/*
 * La idea sería tener un archivo de lectura de este tipo de data en vez de un .h a compilar
*/
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <SDL.h>
#include <iostream>
#include "../core/Vector2D.h"
using namespace std;
using uint = unsigned int;

const Vector2D VECTOR_ZERO = { 0,0 };

// WINDOW ----------------------------------------------------------------------------------------
const uint WIN_WIDTH = 1920;
const uint WIN_HEIGHT = 1080;
const float WIN_WIDTH_PER_PIXEL=WIN_WIDTH/544;
const float WIN_HEIGHT_PER_PIXEL=WIN_HEIGHT/306;
const SDL_Rect FULLWINDOW = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

// FRAME TIMES ------------------------------------------------------------------------------------
const double FRAME_TIME = 30;
const int DELAY_TIME = 17;

// TEXTURES ---------------------------------------------------------------------------------------
const string TEXTURES_FILE = "../Game/src/data/textures.txt"; // Hay que rehacer las movidas bien aquí, en vez del archivo este
const int NUM_TEXTURES = 19;
const int BLOCK_NUMB = 3;
const int DIGITS_NUMB = 4;

// ANIMATIONS -------------------------------------------------------------------------------------
const string ONOUT = "OnOut";
const string ONOVER = "OnOver";
const string ONCLICK = "OnClick";
const string ONLOCKED = "OnLocked";
const string ONCOMPLETED = "OnCompleted";
const string SHUFFLING_CARDS = "ShufflingCards";
const string IDLE = "Idle";
const string REVERSE = "CardReverse";
const string NUMBERS = "Numbers";

// PLAYER -----------------------------------------------------------------------------------------
// PLAYER ANIMATIONS
const string PLAYER = "Player";
const int PLAYER_SPRITE_WIDTH = 17;
const int PLAYER_SPRITE_HEIGHT = 30;
const int PLAYER_SPRITE_ROWS = 2;
const int PLAYER_SPRITE_COLS = 8;
const string PLAYER_IDLE = "PlayerIdle";
const string PLAYER_MOVE = "PlayerMove";
const int PLAYER_IDLE_INITIAL_FRAME = 0;
const int PLAYER_IDLE_FINAL_FRAME = 7;
const int PLAYER_IDLE_FRAME_RATE = 10;
const int PLAYER_MOVE_INITIAL_FRAME = 8;
const int PLAYER_MOVE_FINAL_FRAME = 14;
const int PLAYER_MOVE_FRAME_RATE = 10;
// PLAYER DIMENSIONS
const float PLAYER_INITIAL_WIDTH = PLAYER_SPRITE_WIDTH * 4;
const float PLAYER_INITIAL_HEIGHT = PLAYER_SPRITE_HEIGHT * 4;
const Vector2D PLAYER_INITIAL_POSITION = { WIN_WIDTH / 2.0f - PLAYER_INITIAL_WIDTH / 2, WIN_HEIGHT / 2.0f - PLAYER_INITIAL_HEIGHT / 2};
const Vector2D PLAYER_INITIAL_VELOCITY = { 0.0f, 0.0f };
const float PLAYER_INITIAL_ROTATION = 0;
const float PLAYER_SPEED = 200;

// ENEMIES ---------------------------------------------------------------------------------------
const int ENEMY_WIDTH = 30 * 2;
const int ENEMY_HEIGHT = 60 * 2;
const int BULLET_ANGLE = 20;
const float ENEMY_SPEED = 50;

// BULLETS ---------------------------------------------------------------------------------------

const float BULLET_SPEED = 200;

// BUTTONS ---------------------------------------------------------------------------------------
// BUTTONS DIMENSIONS
const int BUTTON_SPRITE_WIDTH = 79;
const int BUTTON_SPRITE_HEIGHT = 18;
const int BUTTON_SPRITE_COLUMS = 2;
const int BUTTON_SPRITE_ROWS = 6;
const int BUTTON_FRAME_SPRITE_WIDTH = 95;
const int BUTTON_FRAME_SPRITE_HEIGTH = 45;
// ANIMATIONS FRAMERATES
const int ONCLICK_ONOUT_SPEED = 1;
const int ONOVER_SPEED = 10;
// BUTTON FRAMES ANIMATIONS
const int ONOUT_ALL_FRAMES = 10;
const int ONONVER_START_FRAME = 0;
const int ONOVER_END_FRAME = 9;
const int ONCLICK_ALL_FRAMES = 11;
// MAINMENU: BUTTONS POSITIONS AND DIMENSIONS
const int MM_BUTTON_WIDTH = BUTTON_SPRITE_WIDTH * 4;
const int MM_BUTTON_HEIGHT = BUTTON_SPRITE_HEIGHT * 4;
const int MM_BUTTONFRAME_WIDTH = BUTTON_FRAME_SPRITE_WIDTH * 4;
const int MM_BUTTONFRAME_HEIGHT = BUTTON_FRAME_SPRITE_HEIGTH * 4;
const Vector2D MM_PLAY_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - ((BUTTON_SPRITE_WIDTH * 2) + (BUTTON_FRAME_SPRITE_WIDTH * 4)), WIN_HEIGHT * 4 / 8);
const Vector2D MM_OPTIONS_BUTTON_POS = Vector2D(WIN_WIDTH / 3 - BUTTON_SPRITE_WIDTH, WIN_HEIGHT * 5.5 / 8);
const Vector2D MM_ALBUM_BUTTON_POS = Vector2D(WIN_WIDTH / 2 + BUTTON_SPRITE_WIDTH * 2, WIN_HEIGHT * 5.5 / 8);
const Vector2D MM_EXIT_BUTTON_POS = Vector2D(WIN_WIDTH / 2 + (3 * WIN_WIDTH / 20), WIN_HEIGHT * 4 / 8);
const Vector2D MM_PLAYFRAME_BUTTON_POS = MM_PLAY_BUTTON_POS - Vector2D(48, 88);
const Vector2D MM_OPTIONSFRAME_BUTTON_POS = MM_OPTIONS_BUTTON_POS - Vector2D(48, 88);
const Vector2D MM_ALUBMFRAME_BUTTON_POS = MM_ALBUM_BUTTON_POS - Vector2D(48, 88);
const Vector2D MM_EXITFRAME_BUTTON_POS = MM_EXIT_BUTTON_POS - Vector2D(48, 88);
// BUTTON KEYS
const string PLAY = "PlayButton";
const string OPTIONS = "OptionsButton";
const string ALBUM = "AlbumButton";
const string EXIT = "ExitButton";

// FLOOR -----------------------------------------------------------------------------------------
const string FLOOR_PAST = "BattleBackground";
const float FLOOR_WIDTH = 750*WIN_WIDTH_PER_PIXEL; //Dimension horizontal del sprite de suelo
const float FLOOR_HEIGHT = 500 * WIN_HEIGHT_PER_PIXEL; //Dimension vertical del sprite de suelo
const Vector2D FLOOR_PAST_VELOCITY = VECTOR_ZERO;
// LIFEBAR ---------------------------------------------------------------------------------------
const string LIFEBAR = "LifeBar";
const string LIFEFRAME = "LifeFrame";
const string MANAFRAME = "LifeFrameFlipped";
const string MANABAR = "ManaBar";
const Vector2D LIFEBAR_POSITION = { WIN_WIDTH - 213 * 2, 30 };
const Vector2D LIFEBAR_VELOCITY = VECTOR_ZERO;
const Vector2D MANABAR_POSITION = { WIN_WIDTH / 2 - 250, 30};
const Vector2D MANABAR_VELOCITY = VECTOR_ZERO;
const int BAR_WIDTH = 200;
const int BAR_HEIGHT = 30;
const Vector2D LIFE_POSITION = { WIN_WIDTH - 213 * 2 - 13, 10 };
const Vector2D LIFE_VELOCITY = VECTOR_ZERO;
const Vector2D MANA_POSITION = { WIN_WIDTH / 2 - 250, 10 };
const Vector2D MANA_VELOCITY = VECTOR_ZERO;
const int LIFE_WIDTH = 213;
const int LIFE_HEIGHT = 53;
const int MANA_WIDTH = 213;
const int MANA_HEIGHT = 53;

// CARDS -----------------------------------------------------------------------------------------
const int REVERSE_WIDTH = 58 * 2;
const int REVERSE_HEIGHT = 93 * 2;
const int RIGHT_OFFSET = 5 * REVERSE_WIDTH / 4;
const int LEFT_OFFSET = REVERSE_WIDTH / 4;
const int DOWN_OFFSET = WIN_HEIGHT - 6 * REVERSE_HEIGHT / 5;
const int CARD_OFFSET_W = 2 * 2;
const int CARD_OFFSET_H = 21 * 2;
const int MAX_HAND_SIZE = 4;
// CARD DIMENSIONS
const int CARD_WIDTH = 58;
const int CARD_HEIGHT = 93;
// UI CARD DIMENSIONS
const int UI_CARD_WIDTH = CARD_WIDTH * 4;
const int UI_CARD_HEIGHT = CARD_HEIGHT * 4;
// UI CARD POSITIONS
const int Y_CARD_POS = WIN_HEIGHT - WIN_HEIGHT / 8 - CARD_HEIGHT / 2;
const int Y_CARD_POS_SELECTED = WIN_HEIGHT - WIN_HEIGHT / 8 - CARD_HEIGHT / 2 - 60;
const int BETWEEN_CARD_SPACE = CARD_WIDTH * 4 / 2;
const int CENTERED_CARD_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2; // Usada para 3 y 1 cartas en mano
	// 4 CARDS IN HAND
const int X1_4CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 - UI_CARD_WIDTH - BETWEEN_CARD_SPACE;
const int X2_4CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 - BETWEEN_CARD_SPACE; // Usada para 2 cartas en mano
const int X3_4CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 + BETWEEN_CARD_SPACE; // Usada para 2 cartas en mano
const int X4_4CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 + UI_CARD_WIDTH + BETWEEN_CARD_SPACE;
	// 3 CARDS IN HAND
const int X1_3CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 - BETWEEN_CARD_SPACE * 2;
const int X3_3CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 + BETWEEN_CARD_SPACE * 2;

// NUMBERS ---------------------------------------------------------------------------------------
const int NUMBERS_WIDTH = 130;
const int NUMBERS_HEIGHT = 250;
const int NUMBERS_SPRITE_COLUMS = 2;
const int NUMBERS_SPRITE_ROWS = 5;
const int NUM_RENDER_W = NUMBERS_WIDTH / 5 * 2;
const int NUM_RENDER_H = NUMBERS_HEIGHT / 5 * 2;

// LOGO ------------------------------------------------------------------------------------------
const int LOGO_WIDTH = 576;
const int LOGO_HEIGHT = 403;
const Vector2D LOGO_POSITION = {WIN_WIDTH / 2 - LOGO_WIDTH / 2, WIN_HEIGHT / 7};
const int LOGO_ROWS = 1;
const int LOGO_COLUMNS = 4;
const int LOGO_FRAME_WIDTH = 200;
const int LOGO_FRAME_HEIGHT = 140;
const string LOGO_ANIM_KEY = "LogoIdle";
const int LOGO_START_FRAME = 0;
const int LOGO_END_FRAME = 3;
const int LOGO_FRAME_RATE = 4;

// NODOS -----------------------------------------------------------------------------------------
const float NODE_LEVEL_X[3] = { WIN_WIDTH / 7, WIN_WIDTH / 7 * 3, WIN_WIDTH / 7 * 5 };
const float NODE_LEVEL_Y[3] = { WIN_HEIGHT / 7 * 5, WIN_HEIGHT / 7 * 3, WIN_HEIGHT / 7 };
const int NODE_WIDTH = 50;
const int NODE_HEIGHT = 50;

const string BATTLE_NODE_TEXTURE_KEY = "BattleNode";
const string SHOP_NODE_TEXTURE_KEY = "ShopNode";
const string CHEST_NODE_TEXTURE_KEY = "ChestNode";
const string EVENT_NODE_TEXTURE_KEY = "EventNode";

const int NODE_FRAME_WIDTH = 1;
const int NODE_FRAME_HEIGHT = 1;
const int NODE_FRAME_ROWS = 1;
const int NODE_FRAME_COLUMNS = 5;

const int NODE_BUTTON_ONOUT_START_FRAME = 0;
const int NODE_BUTTON_ONOUT_END_FRAME = 0;
const int NODE_BUTTON_ONOVER_START_FRAME = 1;
const int NODE_BUTTON_ONOVER_END_FRAME = 1;
const int NODE_BUTTON_ONCLICK_START_FRAME = 2;
const int NODE_BUTTON_ONCLICK_END_FRAME = 2;
const int NODE_BUTTON_ONLOCKED_START_FRAME = 3;
const int NODE_BUTTON_ONLOCKED_END_FRAME = 3;
const int NODE_BUTTON_ONCOMPLETED_START_FRAME = 4;
const int NODE_BUTTON_ONCOMPLETED_END_FRAME = 4;

// STUDIO ----------------------------------------------------------------------------------------
const int STUDIO_WIDTH = 84 * 3;
const int STUDIO_HEIGTH = 18 * 3;
const Vector2D STUDIO_POSITION = { WIN_WIDTH / 9 - STUDIO_WIDTH / 2, WIN_HEIGHT - WIN_HEIGHT / 10 - 10 };

// MESSAGE ---------------------------------------------------------------------------------------
const int MESSAGE_W = 300;
const int MESSAGE_H = 200;
const int MESSAGE_X = (WIN_WIDTH / 2) - 150;
const int MESSAGE_Y = WIN_HEIGHT / 4;

//ENEMY GENERATOR---------------------------------------------------------------------------------

const int STARTING_SPAWNS[7][3] = {
	{100, 0 ,0},
	{85, 10, 5},
	{70, 20, 10},
    {0, 100,0},
	{40, 40, 20},
	{0, 0, 100},
	{25, 50, 25}
};

const int STANDARD_SPAWNS[30][7] = {
	{50, 30, 20, 0 , 0, 0, 100},
	{46, 29, 19, 3, 0, 2, 100},
	{42, 28, 18, 6, 0, 4, 100},
	{38, 27, 17, 9, 0, 6, 100},
	{34, 26, 16, 12, 0, 8, 100},
	{0, 0, 0, 100, 0, 0, 100},
	{30, 25, 15, 15, 0, 10 ,100},
	{28, 24, 14, 16, 0, 12, 100},
	{26, 23, 13, 17, 0, 14, 100},
	{24, 22, 12, 18, 0, 16, 100},
	{22, 21, 11, 19, 0, 18, 100},
	{0, 0, 0, 0, 0, 100, 0},
	{21, 19, 10, 19, 1, 20, 100},
	{19, 18, 10, 19, 2, 22, 100},
	{17, 17, 10, 18, 3, 24, 100},
	{15, 16, 10, 16, 4, 26, 100},
	{13, 15, 10, 15, 5, 28, 100},
	{0, 0, 0, 0, 0, 0, 100},
	{11, 25, 35, 50, 56, 85, 100},
	{9, 22, 32, 47, 54, 84, 100},
	{7, 19, 29, 44, 52, 83, 100},
	{5, 16, 27, 41, 50, 82, 100},
};

#endif