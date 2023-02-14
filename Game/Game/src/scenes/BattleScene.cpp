#include "BattleScene.h"
#include "../core/SDLApplication.h"

// Constructora
BattleScene::BattleScene(SDLApplication* _game) : GameState(_game) {
	// Quitar cuando se cree el mapa de combate
	floor = new GameObject();
	floor->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	floor->addComponent<Image>(_game->getTexture("Player"), getCamera()->getComponent<Transform>());
	stateScene.push_back(floor);

	player = new Player(_game, getCamera());
	stateScene.push_back(player);
}