#include "ChestScene.h"
#include "../core/SDLApplication.h"

ChestScene::ChestScene(SDLApplication* _game) : GameState(_game) {
	Button* MainMenu = new Button(mainMenu, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT - 50), "Opciones");
	stateScene.push_back(MainMenu);
}
void ChestScene::mainMenu(SDLApplication* _game) {
	SDLApplication::newScene<MapScene>(_game);
}