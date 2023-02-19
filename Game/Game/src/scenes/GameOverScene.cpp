#include "GameOverScene.h"
#include "../core/SDLApplication.h"


GameOverScene::GameOverScene() {
	//Creo el background
	auto bc = addGameObject();
	bc->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	auto i = bc->addComponent<Image>(SDLApplication::getTexture("GameOver"));
	i->attachToCamera();
	//Creo el objeto con la imagen del mensaje de muerte
		GameObject * message = addGameObject();
	message->addComponent<Transform>(Vector2D(MESSAGE_X, MESSAGE_Y), Vector2D(0, 0), MESSAGE_W, MESSAGE_H);
	auto im = message->addComponent<Image>(SDLApplication::getTexture("YouDied"));
	im->attachToCamera();
	//Creo el boton y su marco y los fijo a la camara
	GameObject* marco = addGameObject();
	marco->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 103, WIN_HEIGHT * 2 / 3 - 44), Vector2D(0, 0), 190, 90);
	auto An = marco->addComponent<Animator>(SDLApplication::getTexture("Marco"),
		BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	An->attachToCamera();

	auto but = addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 2 / 3),
		EXIT, BUTTON_SPRITE_WIDTH * 2, BUTTON_SPRITE_HEIGHT * 2, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS,BUTTON_SPRITE_WIDTH,BUTTON_SPRITE_HEIGHT, marco);
	but->getComponent<Animator>()->attachToCamera();
}

void GameOverScene::mainMenu() {
	SDLApplication::newScene<MainMenuScene>();
}