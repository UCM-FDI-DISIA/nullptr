#include "MainMenuScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/GameObject.h"

MainMenuScene::MainMenuScene() : GameState() {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground"));

	// Logo del juego
	GameObject* logo = addGameObject();
	logo->addComponent<Transform>(LOGO_POSITION, Vector2D(), 404, 284);
	Animator* a = logo->addComponent<Animator>(SDLApplication::getTexture("GameLogo"), LOGO_FRAME_WIDTH, LOGO_FRAME_HEIGHT, LOGO_ROWS, LOGO_COLUMNS);
	a->createAnim(LOGO_ANIM_KEY, LOGO_START_FRAME, LOGO_END_FRAME, LOGO_FRAME_RATE, -1);
	a->play(LOGO_ANIM_KEY);

	// Logo del estudio
	GameObject* estudio = addGameObject();
	estudio->addComponent<Transform>(STUDIO_POSITION, Vector2D(), STUDIO_WIDTH, STUDIO_HEIGTH);
	estudio->addComponent<Image>(SDLApplication::getTexture("StudioLogo"));

	//Stats por defecto
	PlayerData::instance()->defaultPlayerStats();

	// Botón jugar
	createButton(MM_PLAY_BUTTON_POS, MM_PLAY_BUTTON_POS - FRAME_OFFSET, []() { SDLApplication::newScene<MapScene>(); }, PLAY);

	// Botón options
	createButton(MM_OPTIONS_BUTTON_POS, MM_OPTIONS_BUTTON_POS - FRAME_OFFSET, []() { SDLApplication::newScene<OptionsMenuScene>(); }, OPTIONS);

	// Botón album
	createButton(MM_ALBUM_BUTTON_POS, MM_ALBUM_BUTTON_POS - FRAME_OFFSET, []() { SDLApplication::newScene<AlbumScene>(); }, ALBUM);

	// Botón salir
	createButton(MM_EXIT_BUTTON_POS, MM_EXIT_BUTTON_POS - FRAME_OFFSET, []() { SDLApplication::instance()->quitGame(); }, EXIT);
}

// Crear un bot�n especificado en la escena
void MainMenuScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key);
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), MM_BUTTONFRAME_WIDTH, MM_BUTTONFRAME_HEIGHT);
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols);

	// Crear bot�n
	addGameObject<Button>(_cb, _bPos, aI, frame);
}