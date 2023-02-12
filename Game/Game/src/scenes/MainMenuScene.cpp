#include "MainMenuScene.h"
#include "../core/SDLApplication.h"
#include "../managers/MainSceneManager.h"

MainMenuScene::MainMenuScene(SDLApplication* _game) : GameState(_game) {
	//// Ejemplo de como añadir un GameObject con transform e image
	//GameObject* ben = new GameObject();
	//ben->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT/2 - 18), Vector2D(0, 0), 158, 36);
	//ben->addComponent<Image>(game->getTexture("Opciones"));
	//stateScene.push_back(ben);

	MainSceneManager* msm = new MainSceneManager(Test, game);
	sceneManagers.push_back(msm);
}

void MainMenuScene::Test() {
	cout << "HE SIDO CLICADO" << endl;
}