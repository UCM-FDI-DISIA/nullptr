#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"

OptionsMenuScene::OptionsMenuScene() : GameState() {
	cout << "Has entrado en la escena de Opciones" << endl;

	addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50),
		EXIT, MAINMENU_BUTTON_WIDTH, MAINMENU_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);

	addGameObject<Button>(toggleScreen, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 200),
		OPTIONS, MAINMENU_BUTTON_WIDTH, MAINMENU_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
}

void OptionsMenuScene::mainMenu() {
	SDLApplication::newScene<MainMenuScene>();
}

void OptionsMenuScene::toggleScreen() {
	SDLUtils::instance()->toggleFullScreen();
}