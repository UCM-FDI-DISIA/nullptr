#include "MainMenuScene.h"
#include "../core/SDLApplication.h"
#include "../managers/MainMenuManager.h"

MainMenuScene::MainMenuScene(SDLApplication* _game) : GameState(_game) {
	//Imagen de fondo
	GameObject* background = new GameObject();
	background->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 800, 600);
	background->addComponent<Image>(game->getTexture("MainMenuFondo"));
	stateScene.push_back(background);

	//Marco de los botones
	for (int i = 0; i < 4; i++) {
		GameObject* marco = new GameObject();
		marco->addComponent<Transform>(Vector2D(WIN_WIDTH/ 2 - 103, (WIN_HEIGHT * (4 + i) / 8) - 44), Vector2D(0, 0), 190, 90);
		Animator* anim = marco->addComponent<Animator>(game->getTexture("MarcoBoton"), 95, 45, 5, 2);
		anim->createAnim("Idle", 0, 9, 5, -1);
		anim->play("Idle");
		stateScene.push_back(marco);
	}

	//Manager de los botones
	MainMenuManager* msm = new MainMenuManager(game);
	sceneManagers.push_back(msm);
}