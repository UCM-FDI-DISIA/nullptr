#include "FuBattleScene.h"
#include "../core/SDLApplication.h"

// Constructora
FuBattleScene::FuBattleScene(SDLApplication* _game) : GameState(_game) {
  cout << "Has entrado en la escena de Batalla" << endl;

	// Quitar cuando se cree el mapa de combate
	floor = new GameObject();
	floor->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	floor->addComponent<Image>(_game->getTexture("Player"), getCamera()->getComponent<Transform>());
	stateScene.push_back(floor);

	player = new Player(_game, getCamera());
	stateScene.push_back(player);
}