#include "MainMenuScene.h"
#include "../core/SDLApplication.h"


MainMenuScene::MainMenuScene(SDLApplication* _game) : GameState(_game) {
	// Ejemplo de como añadir un GameObject con transform e image
	GameObject* ben = new GameObject();
	ben->addComponent<Transform>(Vector2D(0,0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	ben->addComponent<Image>(game->getTexture("PlinPlinPlon"));
	stateScene.push_back(ben);
}