#include "MainSceneManager.h"
#include "../GameObjects/UI/Button.h"
#include "../core/SDLApplication.h"

MainSceneManager::MainSceneManager(CallBack _c, SDLApplication* game) {
	
	Button* button = new Button(_c, game);
	addGameObject(button);
}