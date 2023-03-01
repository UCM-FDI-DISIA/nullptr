#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"

OptionsMenuScene::OptionsMenuScene() : GameState() {
	cout << "Has entrado en la escena de Opciones" << endl;

	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>(_grp_GENERAL, mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);
	aI.key = OPTIONS;
	addGameObject<Button>(_grp_GENERAL, toggleScreen, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 200), aI);
}

void OptionsMenuScene::mainMenu() {
	SDLApplication::newScene<MainMenuScene>();
}

void OptionsMenuScene::toggleScreen() {
	SDLUtils::instance()->toggleFullScreen();
}