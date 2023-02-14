#include "BattleScene.h"
#include "../core/SDLApplication.h"

// Constructora
BattleScene::BattleScene(SDLApplication* _game) : GameState(_game) {
	// Quitar cuando se cree el mapa de combate
	floor = new GameObject();
	floor->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT, 0, *getCamera()->getPosition());
	floor->addComponent<Image>(_game->getTexture("Player"));
	stateScene.push_back(floor);

	player = new Player(_game);
	stateScene.push_back(player);
}

void BattleScene::update() {
	for (GameObject* object : stateScene) {
		if (object->getComponent<Transform>() != nullptr) {
			getCamera()->setPosition(player->getComponent<Transform>()->getPos());
			object->getComponent<Transform>()->setCenter(PLAYER_INITIAL_POSITION - getCamera()->getPosition());
		}
		object->update();
	}
	for (Manager* manager : sceneManagers) {
		manager->update();
	}

	refresh();
}