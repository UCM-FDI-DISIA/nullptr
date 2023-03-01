#include "AlbumScene.h"
#include "../core/SDLApplication.h"

AlbumScene::AlbumScene() : GameState() {
	cout << "Has entrado en la escena del album" << endl;
	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>(_grp_GENERAL, mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);
}
void AlbumScene::mainMenu() {
	SDLApplication::newScene<MainMenuScene>();
}