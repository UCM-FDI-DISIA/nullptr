#pragma once
#include "../utils/Singleton.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

class GameControl : public Singleton<GameControl> {
private:
	bool controller_;
	InputHandler& ih_;

	uint lastMovement, lastMovementU, lastMovementD, lastMovementL, lastMovementR;
	const uint movementDelay, sameDirMovementDelay;

	float movement(SDL_GameControllerAxis axis, SDL_KeyCode minus, SDL_KeyCode plus) const;
	bool attack(SDL_GameControllerButton button, SDL_GameControllerAxis trigger, InputHandler::MOUSEBUTTON mouseButton) const;
	bool adjustCursorToJoystick(SDL_GameControllerAxis xAxis, SDL_GameControllerAxis yAxis) const;
public:
	// Constructora
	GameControl();

	// Eje de movimiento en X, entre -1 y 1
	float movementX() const;
	// Eje de movimiento en Y, entre -1 y 1
	float movementY() const;

	// Acción de ataque básico
	bool basic() const;
	// Acción de habilidad
	bool ability() const;
	// Cambia la posición del cursos en función a los joysticks del mando si el control por este está activado
	bool controllerToCursor() const;

	// Cambiar en partida la carta seleccionada a la izquierda
	bool selectLeftCard() const;
	// Cambiar en partida la carta seleccionada a la derecha
	bool selectRightCard() const;

	// Activar el portal para salir del nivel
	bool completeLevel() const;
	// Pausar el juego
	bool pause() const;

	// Pulsar un botón
	bool click() const;
	// Si está activado el control por mando se mueve el mouse a la posición indicada
	bool moveMouse(float x, float y) const;

	// Seleccionar el botón superior
	bool selectUpButton();
	// Seleccionar el botón inferior
	bool selectDownButton();
	// Seleccionar el botón a la izquierda
	bool selectLeftButton();
	// Seleccionar el botón a la derecha
	bool selectRightButton();

	// Devuelve en valor en el que se deberá mover la cámara cuando se hace scroll
	float scroll(bool controllerScroll = true) const;
	// Ir atrás
	bool goBack() const;

	// Cambiar entre control por mando y control por teclado
	void changeControl();

	// Cambiar a control por teclado
	void changeToKeyboard();

	// Cambiar a control por mando
	void changeToGamepad();

	// Devuelve si el control actual es con mando o no
	inline bool controllerActive() const { return controller_; }
};

inline GameControl& gmCtrl() { return *GameControl::instance(); }
