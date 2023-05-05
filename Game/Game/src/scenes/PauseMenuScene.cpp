#include "PauseMenuScene.h"
#include "../core/SDLApplication.h"

PauseMenuScene::PauseMenuScene() : GameState() {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("OptionsPauseBackground"));

	// Cartel de Pausa
	GameObject* cartel = addGameObject();
	cartel->addComponent<Transform>(PAUSE_MESSAGE_POS, Vector2D(), PAUSE_MESSAGE_W, PAUSE_MESSAGE_H);
	cartel->addComponent<Image>(SDLApplication::getTexture(PAUSE_MESSAGE));

	// Botón jugar
	createButton(PM_RESUME_BUTTON_POS, PM_RESUMEFRAME_BUTTON_POS, []() { sdlutils().focusMouseOnWindow(); SDLApplication::resumeGame(); }, RESUME)->setAsDefaultButton();

	// Botón Opciones
	createButton(PM_OPTIONS_BUTTON_POS, PM_OPTIONSFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

	// Botón salir
	createButton(PM_EXIT_BUTTON_POS, PM_EXITFRAME_BUTTON_POS, []() { pD().loseSavedData(); SDLApplication::newScene<MainMenuScene>();}, EXIT);
	sdlutils().unfocusMouseOnWindow();
}

void PauseMenuScene::handleInput() {
	GameState::handleInput();
	if (gmCtrl_.pause()) {
		SDLApplication::resumeGame();
	}
}