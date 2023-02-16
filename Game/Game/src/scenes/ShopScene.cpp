#include "ShopScene.h"
#include "../core/SDLApplication.h"

ShopScene::ShopScene(SDLApplication* _game) : GameState(_game) {
	cout << "Has entrado en la escena de Tienda" << endl;

	Button* MainMenu = new Button(mainMenu, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50),
		PLAY, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	stateScene.push_back(MainMenu);
}
void ShopScene::mainMenu(SDLApplication* _game) {
	SDLApplication::newScene<MapScene>(_game);
}