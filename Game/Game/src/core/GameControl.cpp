#include "GameControl.h"


float GameControl::movement(SDL_GameControllerAxis axis, SDL_KeyCode minus, SDL_KeyCode plus) {
	if (controller_) {
		return ih_.getNormalizedControllerAxis(axis);
	}
	float ctrl = 0;
	if (ih_.isKeyDown(minus)) ctrl -= 1;
	if (ih_.isKeyDown(plus)) ctrl += 1;
	return ctrl;
}

bool GameControl::attack(SDL_GameControllerButton button, SDL_GameControllerAxis trigger, InputHandler::MOUSEBUTTON mouseButton) {
	if (controller_) {
		return ih_.isControllerButtonDown(button)
			|| ih_.getControllerAxis(trigger) > 0;
	}
	return ih_.getMouseButtonState(mouseButton) == 1;
}

// Eje de movimiento en X, entre -1 y 1
float GameControl::movementX() {
	return movement(SDL_CONTROLLER_AXIS_LEFTX, SDLK_a, SDLK_d);
}
// Eje de movimiento en Y, entre -1 y 1
float GameControl::movementY() {
	return movement(SDL_CONTROLLER_AXIS_LEFTY, SDLK_w, SDLK_s);
}


// Acci�n de ataque b�sico
bool GameControl::basic() {
	return attack(SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, InputHandler::LEFT);		
}
// Acci�n de habilidad
bool GameControl::ability() {
	return attack(SDL_CONTROLLER_BUTTON_B, SDL_CONTROLLER_AXIS_TRIGGERLEFT, InputHandler::RIGHT);
}

bool GameControl::adjustCursorToJoystick(SDL_GameControllerAxis xAxis, SDL_GameControllerAxis yAxis) {
	float x = ih_.getNormalizedControllerAxis(xAxis);
	float y = ih_.getNormalizedControllerAxis(yAxis);
	if (x != 0 || y != 0) {
		SDL_WarpMouseInWindow(sdlutils().window(), sdlutils().width() / 2 + sdlutils().width() / 2 * x, sdlutils().height() / 2 + sdlutils().height() / 2 * y);
		return true;
	}
	return false;
}

// Cambia la posici�n del cursos en funci�n a los joysticks del mando si el control por este est� activado
bool GameControl::controllerToCursor() {
	if (controller_) {
		if (adjustCursorToJoystick(SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY)) return true;
		return adjustCursorToJoystick(SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY);
	}
	return false;
}


// Cambiar en partida la carta seleccionada a la izquierda
bool GameControl::selectLeftCard() {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
			|| ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	}
	return ih_.mouseWheelUp() || ih_.isKeyDown(SDLK_q);
}
// Cambiar en partida la carta seleccionada a la derecha
bool GameControl::selectRightCard() {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
			|| ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	}
	return ih_.mouseWheelDown() || ih_.isKeyDown(SDLK_e);
}

// Activar el portal para salir del nivel
bool GameControl::completeLevel() {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_Y);
	}
	return ih_.isKeyJustDown(SDLK_SPACE);
}
// Pausar el juego
bool GameControl::pause() {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_START);
	}
	return ih_.isKeyDown(SDLK_ESCAPE);
}

// Pulsar un bot�n
bool GameControl::click() {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_A);
	}
	return ih_.getMouseButtonState(InputHandler::LEFT) && ih_.mouseButtonEvent();
}


bool GameControl::moveMouse(float x, float y) {
	if (controller_) {
		SDL_WarpMouseInWindow(sdlutils().window(), x, y);
		return true;
	}
	return false;
}


bool GameControl::selectUpButton() {
	if (controller_) {

		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP);
	}
	return false;
}
bool GameControl::selectDownButton() {
	if (controller_) {

		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN);

	}
	return false;
}
bool GameControl::selectLeftButton() {
	if (controller_) {


		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	}
	return false;
}
bool GameControl::selectRightButton() {
	if (controller_) {


		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	}
	return false;
}