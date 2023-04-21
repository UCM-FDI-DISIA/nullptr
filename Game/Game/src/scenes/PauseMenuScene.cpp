#include "PauseMenuScene.h"
#include "../core/SDLApplication.h"

PauseMenuScene::PauseMenuScene() : GameState() {
	// Bot�n jugar
	createButton(Constant::getVector2D("PM_RESUME_BUTTON_POS"), Constant::getVector2D("PM_RESUMEFRAME_BUTTON_POS"), []() { SDLApplication::resumeGame(); }, Constant::getString("RESUME"));

	// Bot�n options
	createButton(Constant::getVector2D("PM_INVENTORY_BUTTON_POS"), Constant::getVector2D("PM_INVENTORYFRAME_BUTTON_POS"), []() { SDLApplication::pushNewScene<InventoryScene>(); }, Constant::getString("INVENTORY"));

	// Bot�n album
	createButton(Constant::getVector2D("PM_OPTIONS_BUTTON_POS"), Constant::getVector2D("PM_OPTIONSEFRAME_BUTTON_POS"), []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, Constant::getString("OPTIONS"));

	// Bot�n salir
	createButton(Constant::getVector2D("PM_EXIT_BUTTON_POS"), Constant::getVector2D("PM_EXITFRAME_BUTTON_POS"), []() { SDLApplication::pushNewScene<MapScene>(); }, Constant::getString("EXIT"));
}

// Crear un bot�n especificado en la escena
void PauseMenuScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key);

	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), Constant::getInt("MM_BUTTONFRAME_WIDTH"), Constant::getInt("MM_BUTTONFRAME_HEIGHT"));
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), Constant::getInt("BUTTON_FRAME_SPRITE_WIDTH"), Constant::getInt("BUTTON_FRAME_SPRITE_HEIGHT"), aI.rows, aI.cols);

	// Crear bot�n
	addGameObject<Button>(_cb, _bPos, aI, frame);
}