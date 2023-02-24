#include "AlbumScene.h"
#include "../core/SDLApplication.h"

AlbumScene::AlbumScene() : GameState() {
	cout << "Has entrado en la escena del album" << endl;
	addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50),
		EXIT, BUTTON_SPRITE_WIDTH * 4, BUTTON_SPRITE_HEIGHT * 4, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
}
void AlbumScene::mainMenu() {
	SDLApplication::newScene<MainMenuScene>();
}