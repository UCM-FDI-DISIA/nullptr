#include "ChestScene.h"
#include "../core/SDLApplication.h"

ChestScene::ChestScene(SDLApplication* _game) : GameState(_game) {
	cout << "Has entrado en la escena de Cofre" << endl;

	addGameObject<Button>(mainMenu, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50),
		PLAY, MAINMENU_BUTTON_WIDTH, MAINMENU_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
}
void ChestScene::mainMenu(SDLApplication* _game) {
	SDLApplication::newScene<MapScene>(_game);
}