#pragma once
#ifndef SDLAPPLICATION_H_
#define SDLAPPLICATION_H_

#include "../Resource.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "../data/constants.h"
#include "../sdlutils/Texture.h"
#include "GameStateMachine.h"
#include "../scenes/MainMenuScene.h"
#include "../scenes/BattleScene.h"
#include "../sdlutils/InputHandler.h"
using namespace std;

using TextureName = string;

typedef struct {
	string filename;
	uint hframes, vframes;
} TextureDescription;

class SDLApplication {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	unordered_map<TextureName, Texture*> texturesMap;
	GameStateMachine* gameStateMachine = nullptr;

	bool exit;

public:
	// Constructor
	SDLApplication();
	// Destructor
	~SDLApplication();
	// Executes the game
	// Ejecuta el juego
	void run();
	// Draws the game on screen
	// Ejecuta el juego
	void render() const;
	// Updates all the game entities
	// Actualiza todas las entidades del juego
	void update();
	// Updates the game depending on the current event 
	// Actualiza el juego en función al evento actual
	void handleInput();
	// Returns needed texture
	// Devuelve la Texture pedida
	Texture* getTexture(TextureName texture) const;
	// Starts the game
	// Inicia el juego
	static void playGame(SDLApplication* _game);
	// Pauses the game
	// Pausa el juego
	static void pauseGame(SDLApplication* _game);
	// Resumes the game
	// Reanuda el juego
	static void resumeGame(SDLApplication* _game);
	// Pops the top state
	// Elimina el estado en la cima de la pila
	static void popGameState(SDLApplication* _game);
	// Quits the game
	// Cierra el juego
	static void quitGame(SDLApplication* _game);
};
#endif

