#include "BattleScene.h"
#include "../core/SDLApplication.h"

BattleScene::BattleScene(SDLApplication* _game) : GameState(_game) {
	player = new GameObject();
	player->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	player->addComponent<Image>(game->getTexture("Player"));
}