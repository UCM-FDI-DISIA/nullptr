#include "BattleScene.h"
#include "../core/SDLApplication.h"

// Constructora
BattleScene::BattleScene(SDLApplication* _game) : GameState(_game) {
  cout << "Has entrado en la escena de Batalla" << endl;

	// Quitar cuando se cree el mapa de combate
	floor = new GameObject();
	floor->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	floor->addComponent<Image>(_game->getTexture("Player"), getCamera()->getComponent<Transform>());
	stateScene.push_back(floor);
	player = new Player(_game, getCamera());
	stateScene.push_back(new RangedEnemy(game, Vector2D(0, 0), Vector2D(1, 1), 100, static_cast<Player*> (player),this, getCamera()->getComponent<Transform>()));
	stateScene.push_back(new MeleeEnemy(game, Vector2D(0, 10), Vector2D(0, 3), 100, static_cast<Player*>(player), getCamera()->getComponent<Transform>()));


	stateScene.push_back(player);
}