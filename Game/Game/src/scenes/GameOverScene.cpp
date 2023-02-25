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
	createButton(Vector2D(WIN_WIDTH / 2 - 79 * 2, WIN_HEIGHT * 2 / 3), Vector2D(WIN_WIDTH / 2 - 79 * 2, WIN_HEIGHT * 2 / 3) - Vector2D(48, 88),
		[]() { SDLApplication::newScene<MainMenuScene>(); }, EXIT);
}

// Crear un bot�n especificado en la escena
void MainMenuScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), MM_BUTTONFRAME_WIDTH, MM_BUTTONFRAME_HEIGHT);
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols);

	// Crear bot�n
	addGameObject<Button>(_cb, SDLApplication::instance(), _bPos, aI, frame);
}