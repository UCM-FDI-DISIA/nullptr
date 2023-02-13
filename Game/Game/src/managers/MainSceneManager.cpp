#include "MainSceneManager.h"
#include "../GameObjects/UI/Button.h"
#include "../core/SDLApplication.h"

MainSceneManager::MainSceneManager(SDLApplication* game) {
	for (int i = 0; i < 3; i++) {
		Button* button = new Button(Test, game, Vector2D(WIN_WIDTH/2 - 79, (WIN_HEIGHT/2 - 30) + i * 30));
		addGameObject(button);
	}
}

void MainSceneManager::Test(SDLApplication* game) {
	cout << "HE SIDO CLICADO" << endl;
}