#pragma once
#ifndef SDLAPPLICATION_H_
#define SDLAPPLICATION_H_

#include "../Resource.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "../constants.h"
#include "../sdlutils/Texture.h"
#include "GameStateMachine.h"
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
	void run();
	// Draws the game on screen
	void render() const;
	// Updates all the game entities
	void update();
	// Updates the game depending on the current event 
	void handleEvents();
	// Returns needed texture
	Texture* getTexture(TextureName texture) const;
	// Starts the game
	static void playGame(SDLApplication* _game);
	// Pauses the game
	static void pauseGame(SDLApplication* _game);
	// Resumes the game
	static void resumeGame(SDLApplication* _game);
	// Pops the top state
	static void popGameState(SDLApplication* _game);
	// Quits the game
	static void quitGame(SDLApplication* _game);
};
#endif

