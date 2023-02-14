#pragma once
#ifndef BATTLESCENE_H_
#define BATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"

class BattleScene : public GameState {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor;
public:
	// Constructora
	BattleScene(SDLApplication* _game);
};

#endif