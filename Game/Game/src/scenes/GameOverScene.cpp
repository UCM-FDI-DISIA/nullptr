#include "GameOverScene.h"
#include "../core/SDLApplication.h"


GameOverScene::GameOverScene() {
	//Creo el background
	auto bc = addGameObject();
	bc->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	auto i = bc->addComponent<Image>(SDLApplication::getTexture("GameOver"));
	i->attachToCamera();
	//Creo el objeto con la imagen del mensaje de muerte
		GameObject * message = addGameObject();
	message->addComponent<Transform>(Vector2D(MESSAGE_X, MESSAGE_Y), Vector2D(), MESSAGE_W, MESSAGE_H);
	auto im = message->addComponent<Image>(SDLApplication::getTexture("YouDied"));
	im->attachToCamera();
	//Creo el boton y su marco y los fijo a la camara
	GameObject* marco = addGameObject();
	marco->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 2 / 3) - Vector2D(48, 88), Vector2D(), BUTTON_FRAME_SPRITE_WIDTH * 4, BUTTON_FRAME_SPRITE_HEIGTH * 4);
	auto An = marco->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"),
		BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	An->attachToCamera();

	auto but = addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 2 / 3),
		EXIT, BUTTON_SPRITE_WIDTH * 4, BUTTON_SPRITE_HEIGHT * 4, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marco);
	but->getComponent<Animator>()->attachToCamera();
}

void GameOverScene::mainMenu() {
	SDLApplication::newScene<MainMenuScene>();
}