#include "PauseMenuScene.h"
#include "../core/SDLApplication.h"

PauseMenuScene::PauseMenuScene() : GameState() {
	// Botón jugar
	createButton(PM_RESUME_BUTTON_POS, PM_RESUMEFRAME_BUTTON_POS, []() { SDLApplication::resumeGame(); }, RESUME);

	// Botón options
	createButton(PM_INVENTORY_BUTTON_POS, PM_INVENTORYFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<InventoryScene>(); }, INVENTORY);

	// Botón album
	createButton(PM_OPTIONS_BUTTON_POS, PM_OPTIONSFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

	// Botón salir
	createButton(PM_EXIT_BUTTON_POS, PM_EXITFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<MapScene>(); }, EXIT);
}

// Crear un botón especificado en la escena
void PauseMenuScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key);

	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), MM_BUTTONFRAME_WIDTH, MM_BUTTONFRAME_HEIGHT);
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols);

	// Crear botón
	addGameObject<Button>(_cb, _bPos, aI, frame);
}