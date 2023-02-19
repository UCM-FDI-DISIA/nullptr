#include "ShopScene.h"
#include "../core/SDLApplication.h"

ShopScene::ShopScene() : GameState() {
	cout << "Has entrado en la escena de Tienda" << endl;
	addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50),
		PLAY, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
}
void ShopScene::mainMenu() {
	SDLApplication::newScene<MapScene>();
}