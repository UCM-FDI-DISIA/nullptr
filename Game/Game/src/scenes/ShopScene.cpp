#include "ShopScene.h"
#include "../core/SDLApplication.h"

ShopScene::ShopScene() : NodeScene() {
	cout << "Has entrado en la escena de Tienda" << endl;

	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);
}
void ShopScene::mainMenu() {
	SDLApplication::newScene<MapScene>();
}