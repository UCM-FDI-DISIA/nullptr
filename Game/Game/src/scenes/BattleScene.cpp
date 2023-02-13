#include "BattleScene.h"
#include "../core/SDLApplication.h"

// Constructora
BattleScene::BattleScene(SDLApplication* _game) : GameState(_game) {

	player = new Player(_game);
	//player = new Player(_game, camera->getPosition());
	
	stateScene.push_back(player);
}