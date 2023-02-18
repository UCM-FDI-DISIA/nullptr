#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/UI/Button.h"

OptionsMenuScene::OptionsMenuScene(SDLApplication* _game) : GameState(_game) {
	cout << "Has entrado en la escena de Opciones" << endl;

	addGameObject<Button>(mainMenu, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50),
		PLAY, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
}

void OptionsMenuScene::mainMenu(SDLApplication* _game) {
	SDLApplication::newScene<MainMenuScene>(_game);
}