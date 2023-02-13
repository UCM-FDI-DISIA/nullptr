#pragma once
#ifndef BATTLESCENE_H_
#define BATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"

class BattleScene : public GameState {
private:
	Player* player;
	Camera* camera;

public:
	// Constructora
	BattleScene(SDLApplication* _game);
};

#endif