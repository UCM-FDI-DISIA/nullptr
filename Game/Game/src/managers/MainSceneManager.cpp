#include "MainSceneManager.h"
#include "../GameObjects/UI/Button.h"
#include "../core/SDLApplication.h"

MainSceneManager::MainSceneManager(CallBack _c, SDLApplication* game) {
	for (int i = 0; i < 3; i++) {
		Button* button = new Button(_c, game, Vector2D(WIN_WIDTH/2 - 79, (WIN_HEIGHT/2 - 30) + i * 30));
		addGameObject(button);
	}
}