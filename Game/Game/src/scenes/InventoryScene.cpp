#include "InventoryScene.h"
#include "../core/SDLApplication.h"

InventoryScene::InventoryScene() : GameState() {
	// Llamamos a Player data para pillar la info de las cartas que se tienen
	auto info = PlayerData::instance()->getInventoryInfo();
	auto rc = PlayerData::instance()->getReceivedCards();

	createButton(IS_EXIT_BUTTON_POS, IS_EXITFRAME_BUTTON_POS, []() { SDLApplication::popGameState(); }, EXIT);
}

// Crear un bot�n especificado en la escena
void InventoryScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key, IS_BUTTON_WIDTH, IS_BUTTON_HEIGHT);
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), IS_BUTTONFRAME_WIDTH, IS_BUTTONFRAME_HEIGHT);
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols);

	// Crear bot�n
	addGameObject<Button>(_cb, SDLApplication::instance(), _bPos, aI, frame);
}