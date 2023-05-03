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
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground"));

	// Logo del juego
	GameObject* logoShadow = addGameObject();
	GameObject* logo = addGameObject();
	Transform* tr = logo->addComponent<Transform>(LOGO_POSITION, Vector2D(), 404, 284);
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
	if (pD().hasSaveFile()) {
		// Botón jugar
		/*createButton(MM_PLAY_BUTTON_POS, MM_PLAY_BUTTON_POS - FRAME_OFFSET,
			[]() { pD().defaultPlayerStats(); gameMap().reloadMap(); SDLApplication::newScene<MapScene>(); dynamic_cast<MapScene*>(SDLApplication::instance()->getCurrentState())->goToTutorial(); },
			PLAY)->setAsDefaultButton();*/

		//Este es para probar el boss
		createButton(MM_PLAY_BUTTON_POS, MM_PLAY_BUTTON_POS - FRAME_OFFSET,
			[]() { pD().defaultPlayerStats(); gameMap().reloadMap(); SDLApplication::newScene<MapScene>(); dynamic_cast<MapScene*>(SDLApplication::instance()->getCurrentState())->goToBoss(); },
			PLAY)->setAsDefaultButton();

		// Botón continuar
		createButton(MM_RESUME_BUTTON_POS, MM_RESUME_BUTTON_POS - FRAME_OFFSET, []() { pD().getDataFromJSON(); SDLApplication::newScene<MapScene>(); }, CONTINUE);

		// Botón album
		createButton(MM_ALBUM_BUTTON_POS, MM_ALBUM_BUTTON_POS - FRAME_OFFSET, []() { SDLApplication::newScene<AlbumScene>(); }, ALBUM);
	}
	else {
		// Botón jugar
		/*createButton(MM_PLAY_BUTTON_POS_NOSAVE, MM_PLAY_BUTTON_POS_NOSAVE - FRAME_OFFSET,
			[]() { pD().defaultPlayerStats(); gameMap().reloadMap(); SDLApplication::newScene<MapScene>(); dynamic_cast<MapScene*>(SDLApplication::instance()->getCurrentState())->goToTutorial(); },
			PLAY)->setAsDefaultButton();*/

		//Este es para probar el boss
		createButton(MM_PLAY_BUTTON_POS_NOSAVE, MM_PLAY_BUTTON_POS_NOSAVE - FRAME_OFFSET,
			[]() { pD().defaultPlayerStats(); gameMap().reloadMap(); SDLApplication::newScene<MapScene>(); dynamic_cast<MapScene*>(SDLApplication::instance()->getCurrentState())->goToBoss(); },
			PLAY)->setAsDefaultButton();

		// Botón album
		createButton(MM_ALBUM_BUTTON_POS_NOSAVE, MM_ALBUM_BUTTON_POS_NOSAVE - FRAME_OFFSET, []() { SDLApplication::newScene<AlbumScene>(); }, ALBUM);
	}

	// Botón options
	createButton(MM_OPTIONS_BUTTON_POS, MM_OPTIONS_BUTTON_POS - FRAME_OFFSET, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

	// Botón salir
	createButton(MM_EXIT_BUTTON_POS, MM_EXIT_BUTTON_POS - FRAME_OFFSET, []() { SDLApplication::instance()->quitGame(); }, EXIT);
}