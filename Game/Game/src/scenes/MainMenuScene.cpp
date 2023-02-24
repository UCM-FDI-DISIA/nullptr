#include "MainMenuScene.h"
#include "../core/SDLApplication.h"

MainMenuScene::MainMenuScene() : GameState() {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuFondo"));

	// Logo del juego
	GameObject* logo = addGameObject();
	logo->addComponent<Transform>(LOGO_POSITION, Vector2D(), LOGO_WIDTH, LOGO_HEIGHT);
	Animator* a = logo->addComponent<Animator>(SDLApplication::getTexture("Logo"), LOGO_FRAME_WIDTH, LOGO_FRAME_HEIGHT, LOGO_ROWS, LOGO_COLUMNS);
	a->createAnim(LOGO_ANIM_KEY, LOGO_START_FRAME, LOGO_END_FRAME, LOGO_FRAME_RATE, -1);
	a->play(LOGO_ANIM_KEY);

	// Logo del estudio
	GameObject* estudio = addGameObject();
	estudio->addComponent<Transform>(STUDIO_POSITION, Vector2D(), STUDIO_WIDTH, STUDIO_HEIGTH);
	estudio->addComponent<Image>(SDLApplication::getTexture("Estudio"));

	// Botón jugar
	createButton(MM_PLAY_BUTTON_POS, MM_PLAYFRAME_BUTTON_POS, []() { SDLApplication::newScene<MapScene>(); }, PLAY);	

	// Botón options
	createButton(MM_OPTIONS_BUTTON_POS, MM_OPTIONSFRAME_BUTTON_POS, []() { SDLApplication::newScene<OptionsMenuScene>(); }, OPTIONS);

	// Botón album
	createButton(MM_ALBUM_BUTTON_POS, MM_ALUBMFRAME_BUTTON_POS, []() { SDLApplication::newScene<AlbumScene>(); }, ALBUM);

	// Botón salir
	createButton(MM_EXIT_BUTTON_POS, MM_EXITFRAME_BUTTON_POS, []() { SDLApplication::instance()->quitGame(); }, EXIT);
}

// Crear un botón especificado en la escena
void MainMenuScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), BUTTON_FRAME_SPRITE_WIDTH * 4, BUTTON_FRAME_SPRITE_HEIGTH * 4);
	frame->addComponent<Animator>(SDLApplication::getTexture("Marco"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	
	// Crear botón
	addGameObject<Button>(_cb, SDLApplication::instance(), _bPos, key,
		BUTTON_SPRITE_WIDTH * 4, BUTTON_SPRITE_HEIGHT * 4, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, frame);
}