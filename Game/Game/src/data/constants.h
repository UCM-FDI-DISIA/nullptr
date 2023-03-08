
/*
 * La idea sería tener un archivo de lectura de este tipo de data en vez de un .h a compilar
*/
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <SDL.h>
#include <iostream>
#include "../core/Vector2D.h"
#include "../components/ecs.h"

using namespace std;
using uint = unsigned int;

const Vector2D VECTOR_ZERO = { 0,0 };

// WINDOW ----------------------------------------------------------------------------------------
const uint WIN_WIDTH = 1920;
const uint WIN_HEIGHT = 1080;
const SDL_Rect FULLWINDOW = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

const int PIXEL_WIDTH = WIN_WIDTH / 544;
const int PIXEL_HEIGHT = WIN_HEIGHT / 306;

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

// CHARACTER ANIMATOR -----------------------------------------------------------------------------
const string CHARACTER_IDLE_KEY = "charaIdle";
const string CHARACTER_MOVE_KEY = "charaMove";
const string CHARACTER_ATTACK_KEY = "charaAttack";

// PLAYER -----------------------------------------------------------------------------------------
// PLAYER ANIMATIONS
const string PLAYER = "Player";
const int PLAYER_SPRITE_WIDTH = 17;
const int PLAYER_SPRITE_HEIGHT = 30;
const int PLAYER_SPRITE_ROWS = 2;
const int PLAYER_SPRITE_COLS = 8;
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

// MELEE ENEMY
const float MELEE_ENEMY_COOLDOWN = 500;

// RANGED ENEMY
const string RANGED_ENEMY_TEXTURE_KEY = "RangedEnemy";
const int RANGED_ENEMY_SPRITE_WIDTH = 32;
const int RANGED_ENEMY_SPRITE_HEIGHT = 32;
const int RANGED_ENEMY_SPRITE_ROWS = 2;
const int RANGED_ENEMY_SPRITE_COLS = 11;

const int RANGED_ENEMY_WIDTH = RANGED_ENEMY_SPRITE_WIDTH * PIXEL_WIDTH;
const int RANGED_ENEMY_HEIGHT = RANGED_ENEMY_SPRITE_HEIGHT * PIXEL_HEIGHT;

const Animation RANGED_ENEMY_IDLE_ANIMATION(0, 4, 10, -1);
const Animation RANGED_ENEMY_MOVEMENT_ANIMATION(14, 21, 10, -1);
const Animation RANGED_ENEMY_ATTACK_ANIMATION(5, 13, 10, 1);

const int RANGED_ATTACK_ANIM_DELAY = 670;

// TANK ENEMY
const float TANK_SPEED = 35;
const int TANK_ATTACK_DAMAGE = 1;
const int TANK_LIFE = 60;
const float TANK_STOP_TIME = 500;
const float TANK_ATTACK_DISTANCE = 200;
const float TANK_ATTACK_TIME = 3000;

// BULLETS ---------------------------------------------------------------------------------------

const float BULLET_SPEED = 200;
const float THROWN_SPEAR_SPEED = 600;

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
// PAUSEMENU: BUTTON POSITIONS AND DIMENSIONS
const int PM_BUTTON_WIDTH = BUTTON_SPRITE_WIDTH * 4;
const int PM_BUTTON_HEIGHT = BUTTON_SPRITE_HEIGHT * 4;
const int PM_BUTTONFRAME_WIDTH = BUTTON_FRAME_SPRITE_WIDTH * 4;
const int PM_BUTTONFRAME_HEIGHT = BUTTON_FRAME_SPRITE_HEIGTH * 4;
const Vector2D PM_RESUME_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - (PM_BUTTON_WIDTH / 2), WIN_HEIGHT / 2);
const Vector2D PM_INVENTORY_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - (PM_BUTTON_WIDTH / 2), WIN_HEIGHT * 5 / 8);
const Vector2D PM_OPTIONS_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - (PM_BUTTON_WIDTH / 2), WIN_HEIGHT * 6 / 8);
const Vector2D PM_EXIT_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - (PM_BUTTON_WIDTH / 2), WIN_HEIGHT * 7 / 8);
const Vector2D PM_RESUMEFRAME_BUTTON_POS = PM_RESUME_BUTTON_POS - Vector2D(48, 88);
const Vector2D PM_INVENTORYFRAME_BUTTON_POS = PM_INVENTORY_BUTTON_POS - Vector2D(48, 88);
const Vector2D PM_OPTIONSFRAME_BUTTON_POS = PM_OPTIONS_BUTTON_POS - Vector2D(48, 88);
const Vector2D PM_EXITFRAME_BUTTON_POS = PM_EXIT_BUTTON_POS - Vector2D(48, 88);

// BUTTON KEYS
const string PLAY = "PlayButton";
const string OPTIONS = "OptionsButton";
const string ALBUM = "AlbumButton";
const string EXIT = "ExitButton";
const string RESUME = "ResumeButton";
const string INVENTORY = "InventoryButton";

// FLOOR -----------------------------------------------------------------------------------------
const float FLOOR_WIDTH = 6750; //Dimension horizontal del sprite de suelo
const float FLOOR_HEIGHT = 4500; //Dimension vertical del sprite de suelo
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
//CARD DATA
const float SMG_CADENCE = 0.3;
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
const Vector2D NODE_POSITIONS[22] = {
	Vector2D(0, 0),
	Vector2D(5, 5),
	Vector2D(10, 10),
	Vector2D(15, 15),
	Vector2D(20, 20),
	Vector2D(25, 25),
	Vector2D(30, 30),
	Vector2D(35, 35),
	Vector2D(40, 40),
	Vector2D(45, 45),
	Vector2D(50, 50),
	Vector2D(55, 55),
	Vector2D(65, 65),
	Vector2D(70, 70),
	Vector2D(75, 75),
	Vector2D(80, 80),
	Vector2D(90, 90),
	Vector2D(95, 95),
	Vector2D(100, 100),
	Vector2D(105, 105),
	Vector2D(110, 110),
	Vector2D(115, 115)};

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

const int MELEE_RADIUS = 500;
const int RANGED_RADIUS = 800;
const int TANK_RADIUS = 600;

const int STARTING_TIME_PER_WAVE = 15000;

//SPAWNS DE OLEADAS PARA LOS PRIMEROS 4 NODOS
//LOS VALORES GUARDADOS SON LAS PROBABILIDADES DE OLEADAS EN ORDEN
//LOS PORCENTAJES SON ACUMULATIVOS PARA REDUCIR OPERACIONES (ej, si son 15%, 50%, 35%, se guardarian como {15, 65, 100})
const int STARTING_SPAWNS[7][3] = {
	{100, 100, 100},
	{85, 95, 100},
	{70, 90, 100},
	{0, 100, 100},
	{40, 80, 100},
	{0, 0, 100},
	{25, 75, 100}
};

//SPAWNS DE OLEADAS PARA EL RESTO DE NODOS
//HAY UN TOTAL DE 7 TIPOS DE OLEADAS, PARA MAS INFORMACION CONSULTAR EXCEL EN LA CARPETA DE PROYECTOS
const int STANDARD_SPAWNS[30][7] = {
	{50, 80, 100, 100, 100, 100, 100},
	{46, 75, 94, 97, 97, 99, 100},
	{42, 70, 88, 94, 94, 98, 100},
	{38, 65, 82, 91, 91, 97, 100},
	{34, 60, 76, 88, 88, 96, 100},
	{0, 0, 0, 100, 100, 100, 100},
	{30, 55, 70, 85, 85, 95, 100},
	{28, 52, 66, 82, 82, 94, 100},
	{26, 49, 62, 79, 79, 93, 100},
	{24, 46, 58, 76, 76, 92, 100},
	{22, 43, 54, 73, 73, 91, 100},
	{0, 0, 0, 0, 0, 100, 100},
	{21, 40, 50, 69, 70, 90, 100},
	{19, 37, 47, 66, 68, 90, 100},
	{17, 34, 44, 62, 65, 89, 100},
	{15, 31, 41, 51, 55, 81, 100},
	{13, 28, 38, 48, 53, 81, 100},
	{0, 0, 0, 0, 0, 0, 100},
	{11, 25, 35, 50, 56, 85, 100},
	{9, 22, 32, 47, 54, 84, 100},
	{7, 19, 29, 44, 52, 83, 100},
	{5, 16, 26, 41, 50, 82, 100},
	{3, 13, 23, 38, 48, 81, 100},
	{0, 0, 0, 0, 100, 100, 100},
	{2, 10, 19, 34, 46, 80, 100},
	{0, 6, 14, 29, 43, 78, 100},
	{0, 4, 11, 24, 40, 76, 100},
	{0, 2, 8, 19, 37, 74, 100},
	{0, 0, 5, 14, 34, 72, 100},
	{0, 0, 0, 0, 30, 70, 100}
};

//OLEADAS
const int WAVES[7][3] = {
	{8, 0, 0},
	{5, 3, 0},
	{0, 8, 0},
	{6, 0, 1},
	{0, 0, 4},
	{4, 2, 1},
	{0, 4, 2}
};

#endif