#include "ChestScene.h"
#include "../core/SDLApplication.h"

ChestScene::ChestScene() : GameState() {
	cout << "Has entrado en la escena de Cofre" << endl;

	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>(_grp_GENERAL, mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);
}
void ChestScene::mainMenu() {
	SDLApplication::newScene<MapScene>();
}