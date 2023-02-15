
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
#endif