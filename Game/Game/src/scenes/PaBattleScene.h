#pragma once
#ifndef PABATTLESCENE_H_
#define PABATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"

class PaBattleScene : public GameState {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor;
public:
	// Constructora
	PaBattleScene(SDLApplication* _game);
	static void mainMenu(SDLApplication* game);
};

#endif