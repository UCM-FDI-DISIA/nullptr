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
<<<<<<< Updated upstream
=======
#include "../scenes/MainMenuScene.h"
#include "../scenes/BattleScene.h"
#include "../scenes/AlbumScene.h"
#include "../scenes/OptionsMenuScene.h"
#include "../sdlutils/InputHandler.h"
#include "../scenes/ChestScene.h"
#include "../scenes/MapScene.h"
#include "../managers/MainMenuManager.h"

>>>>>>> Stashed changes
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
	void handleEvents();
	// Returns needed texture
	// Devuelve la Texture pedida
	Texture* getTexture(TextureName texture) const;
	// Starts the game
	// Inicia el juego
	static void playGame(SDLApplication* _game);
	//Te lleva al menu de opciones
	static void options(SDLApplication* _game);
	//Te lleva al album de cartas
	static void album(SDLApplication* _game);
	//Te lleva al menu principal
	static void mainMenu(SDLApplication* _game);
	//
	static void beginScene(SDLApplication* game, GameState* newScene);

	template<typename T, typename ...Ts>
	static void newScene(SDLApplication* game, Ts&& ...args) {
		T* scene = new T(game, std::forward<Ts>(args)...);
		game->gameStateMachine->changeState(scene);
	}
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

