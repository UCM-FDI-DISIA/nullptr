#include "MainMenuScene.h"
#include "../core/SDLApplication.h"

MainMenuScene::MainMenuScene() : GameState() {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuFondo"));

	// Logo del juego
	GameObject* logo = addGameObject();
	logo->addComponent<Transform>(LOGO_POSITION, Vector2D(0, 0), LOGO_WIDTH, LOGO_HEIGHT);
	Animator* a = logo->addComponent<Animator>(SDLApplication::getTexture("Logo"), LOGO_FRAME_WIDTH, LOGO_FRAME_HEIGHT, LOGO_ROWS, LOGO_COLUMNS);
	a->createAnim(LOGO_ANIM_KEY, LOGO_START_FRAME, LOGO_END_FRAME, LOGO_FRAME_RATE, -1);
	a->play(LOGO_ANIM_KEY);

	// Logo del estudio
	GameObject* estudio = addGameObject();
	estudio->addComponent<Transform>(STUDIO_POSITION, Vector2D(), STUDIO_WIDTH, STUDIO_HEIGTH);
	estudio->addComponent<Image>(SDLApplication::getTexture("Estudio"));

	// Vector para la asignación del marco a los botones
	vector<GameObject*> marcos(4);

	// BOTONES -> se crean y se añaden a la lista de la escena
	// Botón jugar

	marcos[0] = addGameObject();
	marcos[0]->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - (3 * WIN_WIDTH / 10) - 10, WIN_HEIGHT * 4 / 8 - 88), Vector2D(0, 0), 190 * 2, 90 * 2);
	marcos[0]->addComponent<Animator>(SDLApplication::getTexture("Marco"),
		BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	addGameObject<Button>(play, SDLApplication::instance(),
		Vector2D(WIN_WIDTH / 2 - ((79 * 2) + (190 * 2)) , WIN_HEIGHT * 4 / 8),
		PLAY, MAINMENU_BUTTON_WIDTH * 2, MAINMENU_BUTTON_HEIGHT * 2, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[0]);

	// Botón album
	marcos[1] = addGameObject();
	marcos[1]->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 + BUTTON_SPRITE_WIDTH + 31, WIN_HEIGHT * 5 / 8 - 21), Vector2D(0, 0), 190 * 2, 90 * 2);
	marcos[1]->addComponent<Animator>(SDLApplication::getTexture("Marco"),
		BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	addGameObject<Button>(album, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 + BUTTON_SPRITE_WIDTH * 2, WIN_HEIGHT * 5.5 / 8),
		ALBUM, MAINMENU_BUTTON_WIDTH * 2, MAINMENU_BUTTON_HEIGHT * 2, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[1]);

	// Botón options
	marcos[2] = addGameObject();
	marcos[2]->addComponent<Transform>(Vector2D(WIN_WIDTH / 3 - BUTTON_SPRITE_WIDTH - 48, WIN_HEIGHT * 5 / 8 - 21), Vector2D(0, 0), 190 * 2, 90 * 2);
	marcos[2]->addComponent<Animator>(SDLApplication::getTexture("Marco"),
		BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	addGameObject<Button>(options, SDLApplication::instance(), Vector2D(WIN_WIDTH / 3 - BUTTON_SPRITE_WIDTH, WIN_HEIGHT * 5.5 / 8),
		OPTIONS, MAINMENU_BUTTON_WIDTH * 2, MAINMENU_BUTTON_HEIGHT * 2, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[2]);

	// Botón salir
	marcos[3] = addGameObject();
	marcos[3]->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 + BUTTON_SPRITE_WIDTH * 3 + 3, WIN_HEIGHT * 4 / 8 - 88), Vector2D(0, 0), 190 * 2, 90 * 2);
	marcos[3]->addComponent<Animator>(SDLApplication::getTexture("Marco"),
		BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	addGameObject<Button>(exit, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 + (3 * WIN_WIDTH / 20), WIN_HEIGHT * 4 / 8),
		EXIT, MAINMENU_BUTTON_WIDTH * 2, MAINMENU_BUTTON_HEIGHT * 2, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marcos[3]);
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