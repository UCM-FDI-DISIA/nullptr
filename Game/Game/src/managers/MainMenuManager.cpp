#include "MainMenuManager.h"
#include "../gameObjects/UI/Button.h"
#include "../core/SDLApplication.h"

MainMenuManager::MainMenuManager(SDLApplication* game) {
	for (int i = 0; i < 3; i++) {
		Button* button = new Button(Test, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + i * 30),"Opciones");
		addGameObject(button);
	}
}

void MainMenuManager::Test(SDLApplication* game) {
	cout << "HE SIDO CLICADO" << endl;
}