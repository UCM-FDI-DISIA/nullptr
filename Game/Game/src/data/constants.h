
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
// WINDOW
const uint WIN_WIDTH = 1920;
const uint WIN_HEIGHT = 1080;
const SDL_Rect FULLWINDOW = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

// FRAME TIMES
const double FRAME_TIME = 30;
const int DELAY_TIME = 17;

// TEXTURES
const string TEXTURES_FILE = "../Game/src/data/textures.txt"; // Hay que rehacer las movidas bien aquí, en vez del archivo este
const int NUM_TEXTURES = 19;
const int BLOCK_NUMB = 3;
const int DIGITS_NUMB = 4;

// PLAYER
const float PLAYER_INITIAL_WIDTH = WIN_WIDTH / 10;
const float PLAYER_INITIAL_HEIGHT = WIN_HEIGHT / 10;
const Vector2D PLAYER_INITIAL_POSITION = { WIN_WIDTH / 2.0f - PLAYER_INITIAL_WIDTH / 2, WIN_HEIGHT / 2.0f - PLAYER_INITIAL_HEIGHT / 2};
const Vector2D PLAYER_INITIAL_VELOCITY = { 0.0f, 0.0f };
const float PLAYER_INITIAL_ROTATION = 0;
const float PLAYER_SPEED = 0.001;

// BUTTONS
// Tamaño del sprite
const int BUTTON_SPRITE_WIDTH = 79;
const int BUTTON_SPRITE_HEIGHT = 18;
const int BUTTON_SPRITE_COLUMS = 2;
const int BUTTON_SPRITE_ROWS = 6;
// Tamaño de los botones
const int BUTTON_WIDTH = 158;
const int BUTTON_HEIGHT = 36;
// Velocidades de animaciones
const int ONCLICK_ONOUT_SPEED = 1;
const int ONOVER_SPEED = 10;
// Tamaño de los marcos
const int BUTTON_FRAME_SPRITE_WIDTH = 95;
const int BUTTON_FRAME_SPRITE_HEIGTH = 45;
// Frames de animación
const int ONOUT_ALL_FRAMES = 10;
const int ONONVER_START_FRAME = 0;
const int ONOVER_END_FRAME = 9;
const int ONCLICK_ALL_FRAMES = 11;
// Keys de animación
const string ONOUT = "OnOut";
const string ONOVER = "OnOver";
const string ONCLICK = "OnClick";
// Keys de botones
const string PLAY = "Jugar";
const string OPTIONS = "Opciones";
const string ALBUM = "Album";
const string EXIT = "Salir";

// CARDS
const int REVERSE_WIDTH = 58 * 2;
const int REVERSE_HEIGHT = 93 * 2;
const int RIGHT_OFFSET = 5 * REVERSE_WIDTH / 4;
const int LEFT_OFFSET = REVERSE_WIDTH / 4;
const int DOWN_OFFSET = WIN_HEIGHT - 6 * REVERSE_HEIGHT / 5;
const int CARD_OFFSET_W = 2 * 2;
const int CARD_OFFSET_H = 21 * 2;
const int MAX_HAND_SIZE = 4;
const string PISTOLA = "CPistola";
const int CARD_WIDTH = 58;
const int CARD_HEIGTH = 93;
const int X_CARD_POS = WIN_WIDTH / 6 + LEFT_OFFSET / 2;
const int Y_CARD_POS = WIN_HEIGHT - WIN_HEIGHT / 8 - CARD_HEIGTH / 2;
const int Y_CARD_POS_SELECTED = WIN_HEIGHT - WIN_HEIGHT / 8 - CARD_HEIGTH / 2 - 60;

//NUMBERS
const int NUMBERS_WIDTH = 130;
const int NUMBERS_HEIGHT = 250;
const int NUMBERS_SPRITE_COLUMS = 2;
const int NUMBERS_SPRITE_ROWS = 5;
const int NUM_RENDER_W = NUMBERS_WIDTH / 5 * 2;
const int NUM_RENDER_H = NUMBERS_HEIGHT / 5 * 2;

// Logo
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

// Estudio
const int STUDIO_WIDTH = 84 * 3;
const int STUDIO_HEIGTH = 18 * 3;
const Vector2D STUDIO_POSITION = { WIN_WIDTH / 9 - STUDIO_WIDTH / 2, WIN_HEIGHT - WIN_HEIGHT / 10 - 10 };
#endif