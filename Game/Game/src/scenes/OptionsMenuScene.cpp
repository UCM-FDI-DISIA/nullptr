#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/UI/Button.h"

OptionsMenuScene::OptionsMenuScene(SDLApplication* _game) : GameState(_game) {
	cout << "Has entrado en la escena de Opciones" << endl;

	Button* MainMenu = new Button(mainMenu, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50));
	stateScene.push_back(MainMenu);
}

void OptionsMenuScene::mainMenu(SDLApplication* _game) {
	_game->mainMenu(_game);
}