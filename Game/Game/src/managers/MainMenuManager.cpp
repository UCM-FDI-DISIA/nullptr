#include "MainMenuManager.h"
#include "../GameObjects/UI/Button.h"
#include "../core/SDLApplication.h"

MainMenuManager::MainMenuManager(SDLApplication* game) {
	/*for (int i = 0; i < 3; i++) {
		Button* button = new Button(Test, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + i * 30));
		addGameObject(button);
	}*/

	Button* Play = new Button(play, game, Vector2D(WIN_WIDTH / 2 - 79, 50));
	addGameObject(Play);

	Button* Options = new Button(options, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50));
	addGameObject(Options);

	Button* Album = new Button(album, game, Vector2D(WIN_WIDTH / 2 - 79, (2 * WIN_HEIGHT / 4) + 50));
	addGameObject(Album);

	Button* Exit = new Button(exit, game, Vector2D(WIN_WIDTH / 2 - 79, (3 * WIN_HEIGHT / 4) + 50));
	addGameObject(Exit);
}

void MainMenuManager::play(SDLApplication* game) {
	game->beginScene(game, new BattleScene(game));
}

void MainMenuManager::options(SDLApplication* game) {
	game->beginScene(game, new OptionsMenuScene(game));
}

void MainMenuManager::album(SDLApplication* game) {
	game->beginScene(game, new AlbumScene(game));
}

void MainMenuManager::exit(SDLApplication* game) {
	game->quitGame(game);
}