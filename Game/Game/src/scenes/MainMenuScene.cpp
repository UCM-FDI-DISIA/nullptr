#include "MainMenuScene.h"
#include "../core/SDLApplication.h"
#include "../managers/MainMenuManager.h"

MainMenuScene::MainMenuScene(SDLApplication* _game) : GameState(_game) {
	cout << "Has entrado en la escena del Menu principal" << endl;
	//// Ejemplo de como añadir un GameObject con transform e image
	//GameObject* ben = new GameObject();
	//ben->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT/2 - 18), Vector2D(0, 0), 158, 36);
	//ben->addComponent<Image>(game->getTexture("Opciones"));
	//stateScene.push_back(ben);

	MainMenuManager* msm = new MainMenuManager(game);
	sceneManagers.push_back(msm);
}