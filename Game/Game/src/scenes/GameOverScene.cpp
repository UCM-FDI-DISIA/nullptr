#include "GameOverScene.h"
#include "../core/SDLApplication.h"


GameOverScene::GameOverScene() {
	//Creo el background
	auto bc = addGameObject();
	bc->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	auto i = bc->addComponent<Image>(SDLApplication::getTexture("GameOver"));
	i->attachToCamera();

	//Sonido
	deathSound = &sdlutils().soundEffects().at("Death");

	//Creo el objeto con la imagen del mensaje de muerte
		GameObject * message = addGameObject();
	message->addComponent<Transform>(Vector2D(MESSAGE_X, MESSAGE_Y), Vector2D(), MESSAGE_W, MESSAGE_H);
	auto im = message->addComponent<Image>(SDLApplication::getTexture("YouDied"));
	im->attachToCamera();

	deathSound->play();

	//Creo el boton y su marco y los fijo a la camara
	createButton(Vector2D(WIN_WIDTH / 2 - 79 * 1.5, WIN_HEIGHT * 2 / 3), Vector2D(WIN_WIDTH / 2 - 79 * 1.5, WIN_HEIGHT * 2 / 3) - FRAME_OFFSET,
		[]() { 
			SDLApplication::newScene<MainMenuScene>();
		},
		EXIT)->setAsDefaultButton();
}

GameOverScene::~GameOverScene() {
	deathSound->haltChannel();
}