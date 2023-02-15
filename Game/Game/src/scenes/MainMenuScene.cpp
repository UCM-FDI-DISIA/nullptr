#include "MainMenuScene.h"
#include "../core/SDLApplication.h"
#include "../managers/MainMenuManager.h"

MainMenuScene::MainMenuScene(SDLApplication* _game) : GameState(_game) {
	for (int i = 0; i < 4; i++) {
		GameObject* marco = new GameObject();
		marco->addComponent<Transform>(Vector2D(WIN_WIDTH/ 2 - 92, (WIN_HEIGHT * (4 + i) / 8) - 44), Vector2D(0, 0), 190, 90);
		Animator* anim = marco->addComponent<Animator>(game->getTexture("MarcoBoton"), 95, 45, 5, 2);
		anim->createAnim("Idle", 0, 9, 5, -1);
		anim->play("Idle");
		stateScene.push_back(marco);
	}

	MainMenuManager* msm = new MainMenuManager(game);
	sceneManagers.push_back(msm);
}