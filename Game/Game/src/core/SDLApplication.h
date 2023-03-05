#pragma once
#ifndef SDLAPPLICATION_H_
#define SDLAPPLICATION_H_

#include "../Resource.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "../sdlutils/SDLUtils.h"
#include "../data/constants.h"
#include "../sdlutils/Texture.h"
#include "GameStateMachine.h"
#include "../sdlutils/InputHandler.h"
#include "../gameObjects/UI/Button.h"
#include "../scenes/AlbumScene.h"
#include "../scenes/BattleScene.h"
#include "../scenes/ChestScene.h"
#include "../scenes/InventoryScene.h"
#include "../scenes/MainMenuScene.h"
#include "../scenes/MapScene.h"
#include "../scenes/OptionsMenuScene.h"
#include "../scenes/PauseMenuScene.h"
#include "../scenes/ShopScene.h"
#include "../scenes/GameOverScene.h"

#include "../node/Node.h"

using namespace std;
using TextureName = string;

class SDLApplication: public Singleton<SDLApplication> {
private:
	SDLUtils* utils = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStateMachine = nullptr;
	bool exit;

	double deltaTime = 0.0;
	Uint32 timeOffset = 0;
	uint32_t startTime;

public:
	// Constructora
	SDLApplication();
	// Destructora
	~SDLApplication();
	// Ejecuta el juego
	void run();
	// Ejecuta el juego
	void render() const;
	// Actualiza todas las entidades del juego
	void update();
	// Actualiza el juego en funci�n al evento actual
	void handleInput();
	// Devuelve la Texture pedida
	static Texture* getTexture(TextureName texture);

	template<typename T, typename ...Ts>
	static void newScene(Ts&& ...args) {
		T* scene = new T(std::forward<Ts>(args)...);
		SDLApplication::instance()->gameStateMachine->changeState(scene);
	}
	
	// Pausa el juego
	static void pauseGame();
	// Reanuda el juego
	static void resumeGame();
	// Elimina el estado en la cima de la pila
	static void popGameState();
	// Cierra el juego
	static void quitGame();

	inline double getDeltaTime() { return deltaTime; }
	inline uint32_t getCurrentTime() { return SDL_GetTicks() - timeOffset; }
	inline double getDeltaTimeSeconds() { return getDeltaTime() / 1000.0; }

	
};
#endif

