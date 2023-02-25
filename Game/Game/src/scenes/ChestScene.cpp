#include "ChestScene.h"
#include "../core/SDLApplication.h"

ChestScene::ChestScene() : GameState() {
	cout << "Has entrado en la escena de Cofre" << endl;

	AnimatorInfo aI = AnimatorInfo(EXIT, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH * 4, BUTTON_SPRITE_HEIGHT * 4, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);
}
void ChestScene::mainMenu() {
	SDLApplication::newScene<MapScene>();
}