#include "MainMenuManager.h"
#include "../GameObjects/UI/Button.h"
#include "../core/SDLApplication.h"

MainMenuManager::MainMenuManager(SDLApplication* game) {
	/*for (int i = 0; i < 3; i++) {
		Button* button = new Button(Test, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + i * 30));
		addGameObject(button);
	}*/

	Button* Play = new Button(play, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT/2), "Opciones");
	addGameObject(Play);

	Button* Options = new Button(options, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 5 / 8), "Opciones");
	addGameObject(Options);

	Button* Album = new Button(album, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 6 / 8), "Opciones");
	addGameObject(Album);

	Button* Exit = new Button(exit, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 7 / 8), "Opciones");
	addGameObject(Exit);
	
}

void MainMenuManager::play(SDLApplication* game) {
	SDLApplication::newScene<MapScene>(game);
}

void MainMenuManager::options(SDLApplication* game) {
	SDLApplication::newScene<OptionsMenuScene>(game);
}

void MainMenuManager::album(SDLApplication* game) {
	SDLApplication::newScene<AlbumScene>(game);
}

void MainMenuManager::exit(SDLApplication* game) {
	game->quitGame(game);
}