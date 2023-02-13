#include "BattleScene.h"
#include "../core/SDLApplication.h"

// Constructora
BattleScene::BattleScene(SDLApplication* _game) : GameState(_game) {
	player = new GameObject();
	player->addComponent<Transform>(Vector2D(WIN_WIDTH/2, WIN_HEIGHT/2), Vector2D(0, 0), WIN_WIDTH / 10, WIN_HEIGHT / 10);
	player->addComponent<Image>(game->getTexture("Player"));
	player->addComponent<PlayerMovementComponent>();
	
	camera = new Camera(player);

	stateScene.push_back(player);
	stateScene.push_back(camera);
}

// Renderiza la escena dependiendo de la camara
// Se sobreescribe el render modificando el rect de los gObjs
//void BattleScene::render() const {
//
//}