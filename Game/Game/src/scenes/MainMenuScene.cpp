#include "MainMenuScene.h"
#include "../core/SDLApplication.h"

MainMenuScene::MainMenuScene() : GameState() {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 800, 600);
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuFondo"));

	GameObject* logo = addGameObject();
	logo->addComponent<Transform>(LOGO_POSITION, Vector2D(0, 0), LOGO_WIDTH, LOGO_HEIGHT);
	Animator* a = logo->addComponent<Animator>(SDLApplication::getTexture("Logo"), LOGO_FRAME_WIDTH, LOGO_FRAME_HEIGHT, LOGO_ROWS, LOGO_COLUMNS);
	a->createAnim(LOGO_ANIM_KEY, LOGO_START_FRAME, LOGO_END_FRAME, LOGO_FRAME_RATE, -1);
	a->play(LOGO_ANIM_KEY);

	// Vector para la asignación del marco a los botones
	vector<GameObject*> marcos(4);
	// Marco de los botones
	for (int i = 0; i < 4; i++) {
		marcos[i] = addGameObject();
		marcos[i]->addComponent<Transform>(Vector2D(WIN_WIDTH/ 2 - 103, (WIN_HEIGHT * (4 + i) / 8) - 44), Vector2D(0, 0), 190, 90);
		marcos[i]->addComponent<Animator>(SDLApplication::getTexture("Marco"),
			BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	}

	// BOTONES -> se crean y se añaden a la lista de la escena
	// Botón jugar
	addGameObject<Button>(play, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT / 2),
		PLAY, MAINMENU_BUTTON_WIDTH, MAINMENU_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[0]);

	// Botón opciones
	addGameObject<Button>(options, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 5 / 8),
		OPTIONS, MAINMENU_BUTTON_WIDTH, MAINMENU_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[1]);

	// Botón album
	addGameObject<Button>(album, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 6 / 8),
		ALBUM, MAINMENU_BUTTON_WIDTH, MAINMENU_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[2]);

	// Botón salir
	addGameObject<Button>(exit, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 7 / 8),
		EXIT, MAINMENU_BUTTON_WIDTH, MAINMENU_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[3]);
}

void MainMenuScene::play() {
	SDLApplication::newScene<MapScene>();
}

void MainMenuScene::options() {
	SDLApplication::newScene<OptionsMenuScene>();
}

void MainMenuScene::album() {
	SDLApplication::newScene<AlbumScene>();
}

void MainMenuScene::exit() {
	SDLApplication::instance()->quitGame();
}