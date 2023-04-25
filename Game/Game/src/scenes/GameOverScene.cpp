#include "GameOverScene.h"
#include "../core/SDLApplication.h"


GameOverScene::GameOverScene() {
	//Creo el background
	auto bc = addGameObject();
	bc->addComponent<Transform>(Vector2D(), Vector2D(), Constant::getInt("WIN_WIDTH"), Constant::getInt("WIN_HEIGHT"));
	auto i = bc->addComponent<Image>(SDLApplication::getTexture("GameOver"));
	i->attachToCamera();

	//Sonido
	deathSound = &sdlutils().soundEffects().at(Constant::getString("DEATH_MELODY"));

	//Creo el objeto con la imagen del mensaje de muerte
		GameObject * message = addGameObject();
	message->addComponent<Transform>(Vector2D(Constant::getInt("MESSAGE_X"), Constant::getInt("MESSAGE_Y")), Vector2D(), Constant::getInt("MESSAGE_W"), Constant::getInt("MESSAGE_H"));
	auto im = message->addComponent<Image>(SDLApplication::getTexture("YouDied"));
	im->attachToCamera();

	deathSound->play();

	//Creo el boton y su marco y los fijo a la camara
	createButton(Vector2D(Constant::getInt("WIN_WIDTH") / 2 - 79 * 1.5, Constant::getInt("WIN_HEIGHT") * 2 / 3), Vector2D(Constant::getInt("WIN_WIDTH") / 2 - 79 * 1.5, Constant::getInt("WIN_HEIGHT") * 2 / 3) - Constant::getVector2D("FRAME_OFFSET"),
		[]() { 
			SDLApplication::newScene<MainMenuScene>();

		}, Constant::getString("EXIT"));
}

// Crear un botón especificado en la escena
void GameOverScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key);

	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), Constant::getInt("MM_BUTTONFRAME_WIDTH"), Constant::getInt("MM_BUTTONFRAME_HEIGHT"));
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), Constant::getInt("BUTTON_FRAME_SPRITE_WIDTH"), Constant::getInt("BUTTON_FRAME_SPRITE_HEIGHT"), aI.rows, aI.cols);

	// Crear botón
	addGameObject<Button>(_cb, _bPos, aI, frame);
}

GameOverScene::~GameOverScene() {
	deathSound->haltChannel();
}