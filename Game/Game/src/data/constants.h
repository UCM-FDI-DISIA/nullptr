
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
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
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
const Vector2D PLAYER_INITIAL_POSITION = { WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f };
const float PLAYER_INITIAL_WIDTH = WIN_WIDTH / 10;
const float PLAYER_INITIAL_HEIGHT = WIN_HEIGHT / 10;
const Vector2D PLAYER_INITIAL_VELOCITY = { 0.0f, 0.0f };
const float PLAYER_INITIAL_ROTATION = 0;

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
const int REVERSE_WIDTH = 58;
const int REVERSE_HEIGHT = 93;
#endif