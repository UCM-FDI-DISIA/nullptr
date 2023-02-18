#include "MainMenuScene.h"
#include "../core/SDLApplication.h"

MainMenuScene::MainMenuScene(SDLApplication* _game) : GameState(_game) {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 800, 600);
	background->addComponent<Image>(game->getTexture("MainMenuFondo"));

	GameObject* logo = addGameObject();
	logo->addComponent<Transform>(LOGO_POSITION, Vector2D(0, 0), LOGO_WIDTH, LOGO_HEIGHT);
	Animator* a = logo->addComponent<Animator>(game->getTexture("Logo"), LOGO_FRAME_WIDTH, LOGO_FRAME_HEIGHT, LOGO_ROWS, LOGO_COLUMNS);
	a->createAnim(LOGO_ANIM_KEY, LOGO_START_FRAME, LOGO_END_FRAME, LOGO_FRAME_RATE, -1);
	a->play(LOGO_ANIM_KEY);


	// Vector para la asignación del marco a los botones
	vector<GameObject*> marcos(4);
	// Marco de los botones
	for (int i = 0; i < 4; i++) {
		marcos[i] = addGameObject();
		marcos[i]->addComponent<Transform>(Vector2D(WIN_WIDTH/ 2 - 103, (WIN_HEIGHT * (4 + i) / 8) - 44), Vector2D(0, 0), 190, 90);
		marcos[i]->addComponent<Animator>(game->getTexture("Marco"),
			BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	}

	// BOTONES -> se crean y se añaden a la lista de la escena
	// Botón jugar
	addGameObject<Button>(play, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT / 2),
		PLAY, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[0]);

	// Botón opciones
	addGameObject<Button>(options, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 5 / 8),
		OPTIONS, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[1]);

	// Botón album
	addGameObject<Button>(album, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 6 / 8),
		ALBUM, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[2]);

	// Botón salir
	addGameObject<Button>(exit, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 7 / 8),
		EXIT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[3]);
}

void MainMenuScene::play(SDLApplication* game) {
	SDLApplication::newScene<MapScene>(game);
}

void MainMenuScene::options(SDLApplication* game) {
	SDLApplication::newScene<OptionsMenuScene>(game);
}

void MainMenuScene::album(SDLApplication* game) {
	SDLApplication::newScene<AlbumScene>(game);
}

void MainMenuScene::exit(SDLApplication* game) {
	game->quitGame(game);
}