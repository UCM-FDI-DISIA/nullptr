#pragma once

#include "resource.h"
#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Texture.h"
#include "GameStateMachine.h"
using namespace std;

using TextureName = string;

typedef struct {
	string filename;
	uint hframes, vframes;
} TextureDescription;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	unordered_map<TextureName, Texture*> texturesMap;
	GameStateMachine* gameStateMachine = nullptr;

	bool exit;

public:
	// Constructor
	Game();
	// Destructor
	~Game();
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
	static void playGame(Game* _game);
	// Pauses the game
	static void pauseGame(Game* _game);
	// Resumes the game
	static void resumeGame(Game* _game);
	// Loads a game
	static void loadGame(Game* _game);
	// Starts the set file menu and loads a game
	static void loadGameMenu(Game* _game);
	// Saves the game
	static void saveGame(Game* _game);
	// Starts the set file menu and saves a game
	static void saveGameMenu(Game* _game);
	// Pops the top state
	static void popGameState(Game* _game);
	// Exits to the game menu
	static void exitToGameMenu(Game* _game);
	// Enters the winMenu 
	static void winGameMenu(Game* _game);
	// Enters the loseMenu
	static void loseGameMenu(Game* _game);
	// Quits the game
	static void quitGame(Game* _game);
};
#endif

