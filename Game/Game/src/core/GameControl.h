#pragma once
#include "../utils/Singleton.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
class GameControl : public Singleton<GameControl> {
private:
	bool controller_;
	InputHandler& ih_;

	float movement(SDL_GameControllerAxis axis, SDL_KeyCode minus, SDL_KeyCode plus);
	bool attack(SDL_GameControllerButton button, SDL_GameControllerAxis trigger, InputHandler::MOUSEBUTTON mouseButton);
	bool adjustCursorToJoystick(SDL_GameControllerAxis xAxis, SDL_GameControllerAxis yAxis);
public:
	GameControl() : ih_(ih()), controller_(true) {}

	// Eje de movimiento en X, entre -1 y 1
	float movementX();
	// Eje de movimiento en Y, entre -1 y 1
	float movementY();

	// Acción de ataque básico
	bool basic();
	// Acción de habilidad
	bool ability();
	// Cambia la posición del cursos en función a los joysticks del mando si el control por este está activado
	bool controllerToCursor();

	// Cambiar en partida la carta seleccionada a la izquierda
	bool selectLeftCard();
	// Cambiar en partida la carta seleccionada a la derecha
	bool selectRightCard();

	// Activar el portal para salir del nivel
	bool completeLevel();
	// Pausar el juego
	bool pause();

	// Pulsar un botón
	bool click();
	// 
	bool moveMouse(float x, float y);

	bool selectUpButton();
	bool selectDownButton();
	bool selectLeftButton();
	bool selectRightButton();

	// Cambiar entre control por mando y control por teclado
	inline void changeControl() {
		controller_ = !controller_;
	}
};

inline GameControl& gmCtrl() { return *GameControl::instance(); }
