#include "MainMenuScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/GameObject.h"

MainMenuScene::MainMenuScene() : GameState() {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), Constant::getInt("WIN_WIDTH"), Constant::getInt("WIN_HEIGHT"));
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground"));

	// Logo del juego
	GameObject* logo = addGameObject();
	logo->addComponent<Transform>(Constant::getVector2D("LOGO_POSITION"), Vector2D(), 404, 284);
	Animator* a = logo->addComponent<Animator>(SDLApplication::getTexture("GameLogo"), Constant::getInt("LOGO_FRAME_WIDTH"), Constant::getInt("LOGO_FRAME_HEIGHT"), Constant::getInt("LOGO_ROWS"), Constant::getInt("LOGO_COLUMNS"));
	a->createAnim(Constant::getString("LOGO_ANIM_KEY"), Constant::getInt("LOGO_START_FRAME"), Constant::getInt("LOGO_END_FRAME"), Constant::getInt("LOGO_FRAME_RATE"), -1);
	a->play(Constant::getString("LOGO_ANIM_KEY"));

	// Logo del estudio
	GameObject* estudio = addGameObject();
	estudio->addComponent<Transform>(Constant::getVector2D("STUDIO_POSITION"), Vector2D(), Constant::getInt("STUDIO_WIDTH"), Constant::getInt("STUDIO_HEIGHT"));
	estudio->addComponent<Image>(SDLApplication::getTexture("StudioLogo"));

	//Stats por defecto
	PlayerData::instance()->defaultPlayerStats();

	// Botón jugar
	createButton(Constant::getVector2D("MM_PLAY_BUTTON_POS"), Constant::getVector2D("MM_PLAY_BUTTON_POS") - Constant::getVector2D("FRAME_OFFSET"), []() { SDLApplication::newScene<MapScene>(); }, Constant::getString("PLAY"));

	// Botón options
	createButton(Constant::getVector2D("MM_OPTIONS_BUTTON_POS"), Constant::getVector2D("MM_OPTIONS_BUTTON_POS") - Constant::getVector2D("FRAME_OFFSET"), []() { SDLApplication::newScene<OptionsMenuScene>(); }, Constant::getString("OPTIONS"));

	// Botón album
	createButton(Constant::getVector2D("MM_ALBUM_BUTTON_POS"), Constant::getVector2D("MM_ALBUM_BUTTON_POS") - Constant::getVector2D("FRAME_OFFSET"), []() { SDLApplication::newScene<AlbumScene>(); }, Constant::getString("ALBUM"));

	// Botón salir
	createButton(Constant::getVector2D("MM_EXIT_BUTTON_POS"), Constant::getVector2D("MM_EXIT_BUTTON_POS") - Constant::getVector2D("FRAME_OFFSET"), []() { SDLApplication::instance()->quitGame(); }, Constant::getString("EXIT"));
}

// Crear un bot�n especificado en la escena
void MainMenuScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key);
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), Constant::getFloat("MM_BUTTONFRAME_WIDTH"), Constant::getFloat("MM_BUTTONFRAME_HEIGHT"));
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), Constant::getInt("BUTTON_FRAME_SPRITE_WIDTH"), Constant::getInt("BUTTON_FRAME_SPRITE_HEIGHT"), aI.rows, aI.cols);

	// Crear bot�n
	addGameObject<Button>(_cb, _bPos, aI, frame);
}