#include "MainMenuScene.h"
#include "../core/SDLApplication.h"

MainMenuScene::MainMenuScene(SDLApplication* _game) : GameState(_game) {
	// Imagen de fondo
	GameObject* background = new GameObject();
	background->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 800, 600);
	background->addComponent<Image>(game->getTexture("MainMenuFondo"));
	stateScene.push_back(background);

	GameObject* logo = new GameObject();
	logo->addComponent<Transform>(LOGO_POSITION, Vector2D(0, 0), LOGO_WIDTH, LOGO_HEIGHT);
	Animator* a = logo->addComponent<Animator>(game->getTexture("Logo"), LOGO_FRAME_WIDTH, LOGO_FRAME_HEIGHT, LOGO_ROWS, LOGO_COLUMNS);
	a->createAnim(LOGO_ANIM_KEY, LOGO_START_FRAME, LOGO_END_FRAME, LOGO_FRAME_RATE, -1);
	a->play(LOGO_ANIM_KEY);
	stateScene.push_back(logo);

	// Marco de los botones
	for (int i = 0; i < 4; i++) {
		GameObject* marco = new GameObject();
		marco->addComponent<Transform>(Vector2D(WIN_WIDTH/ 2 - 103, (WIN_HEIGHT * (4 + i) / 8) - 44), Vector2D(0, 0), 190, 90);
		marco->addComponent<Animator>(game->getTexture("Marco"),
			BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
		stateScene.push_back(marco);
	}
	
	// Iterador para la asignación del marco creado anteriormente para cada botón
	list<GameObject*>::iterator it = stateScene.begin(); 
	it++; it++; it++; // Saltar la cámara y el fondo

	// BOTONES -> se crean y se añaden a la lista de la escena
	// Botón jugar
	Button* Play = new Button(play, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT / 2),
		PLAY, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, *it);
	stateScene.push_back(Play);

	// Botón opciones
	it++;
	Button* Options = new Button(options, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 5 / 8),
		OPTIONS, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, *it);
	stateScene.push_back(Options);

	// Botón album
	it++;
	Button* Album = new Button(album, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 6 / 8),
		ALBUM, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, *it);
	stateScene.push_back(Album);

	// Botón salir
	it++;
	Button* Exit = new Button(exit, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 7 / 8),
		EXIT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, *it);
	stateScene.push_back(Exit);
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