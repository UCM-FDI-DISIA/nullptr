#include "MainMenuScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/GameObject.h"

MainMenuScene::MainMenuScene() {
	if (!SDLApplication::instance()->isMusicPlaying()) {
		SDLApplication::instance()->playMainMusic();
	}
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	if (!pD().hasSaveFile()) background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground1"));
	else background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground2"));

	// Logo del juego
	GameObject* logoShadow = addGameObject();
	GameObject* logo = addGameObject();
	Vector2D pos = Vector2D(WIN_WIDTH / 4 - LOGO_WIDTH / 4, WIN_HEIGHT / 2 - LOGO_HEIGHT / 2);
	Transform* tr = logo->addComponent<Transform>(pos, Vector2D(), 404, 284);
	Animator* a = logo->addComponent<Animator>(SDLApplication::getTexture("GameLogo"), LOGO_FRAME_WIDTH, LOGO_FRAME_HEIGHT, LOGO_ROWS, LOGO_COLUMNS);
	a->createAnim(LOGO_ANIM_KEY, LOGO_START_FRAME, LOGO_END_FRAME, LOGO_FRAME_RATE, -1);
	a->play(LOGO_ANIM_KEY);
	logoShadow->addComponent<Transform>(tr->getPos() + Vector2D(4, 4), Vector2D(), 404, 284);
	a = logoShadow->addComponent<Animator>(SDLApplication::getTexture("GameLogoShadow"), LOGO_FRAME_WIDTH, LOGO_FRAME_HEIGHT, LOGO_ROWS, LOGO_COLUMNS);
	a->createAnim(LOGO_ANIM_KEY, LOGO_START_FRAME, LOGO_END_FRAME, LOGO_FRAME_RATE, -1);
	a->play(LOGO_ANIM_KEY);


	// Logo del estudio
	GameObject* estudio = addGameObject();
	estudio->addComponent<Transform>(STUDIO_POSITION, Vector2D(), STUDIO_WIDTH, STUDIO_HEIGTH);
	estudio->addComponent<Image>(SDLApplication::getTexture("StudioLogo"));

	//Stats por defecto
	PlayerData::instance()->defaultPlayerStats();

	// Botón jugar
	if (!pD().hasSaveFile()) { 
		pos = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 3, WIN_HEIGHT * 0.24);
		createButton(pos, pos - FRAME_OFFSET,
			[]() { pD().defaultPlayerStats(); gameMap().reloadMap(); SDLApplication::newScene<MapScene>(); dynamic_cast<MapScene*>(SDLApplication::instance()->getCurrentState())->goToTutorial(); },
			PLAY)->setAsDefaultButton();

		// Botón options
		pos = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 3, WIN_HEIGHT * 0.39);
		createButton(pos, pos - FRAME_OFFSET, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

		// Botón album
		pos = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 3, WIN_HEIGHT * 0.54);
		createButton(pos, pos - FRAME_OFFSET, []() { SDLApplication::newScene<AlbumScene>(); }, ALBUM);

		// Botón salir
		pos = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 3, WIN_HEIGHT * 0.69);
		createButton(pos, pos - FRAME_OFFSET, []() { SDLApplication::instance()->quitGame(); }, EXIT);
	}
	else {
		pos = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 3, WIN_HEIGHT * 0.16);
		createButton(pos, pos - FRAME_OFFSET,
			[]() { pD().defaultPlayerStats(); gameMap().reloadMap(); SDLApplication::newScene<MapScene>(); dynamic_cast<MapScene*>(SDLApplication::instance()->getCurrentState())->goToTutorial(); },
			PLAY)->setAsDefaultButton();

		pos = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 3, WIN_HEIGHT * 0.31);
		createButton(pos, pos - FRAME_OFFSET, []() { pD().getDataFromJSON(); SDLApplication::newScene<MapScene>(); }, CONTINUE);
		
		// Botón options
		pos = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 3, WIN_HEIGHT * 0.46);
		createButton(pos, pos - FRAME_OFFSET, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

		// Botón album
		pos = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 3, WIN_HEIGHT * 0.61);
		createButton(pos, pos - FRAME_OFFSET, []() { SDLApplication::newScene<AlbumScene>(); }, ALBUM);

		// Botón salir
		pos = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 3, WIN_HEIGHT * 0.76);
		createButton(pos, pos - FRAME_OFFSET, []() { SDLApplication::instance()->quitGame(); }, EXIT);

		
	}
	
}