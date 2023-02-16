#pragma once
#ifndef PREBATTLESCENE_H_
#define PREBATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"

class PreBattleScene : public GameState {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor;
public:
	// Constructora
	PreBattleScene(SDLApplication* _game);
};

#endif