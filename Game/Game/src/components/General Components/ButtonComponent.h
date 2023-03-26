#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/Animator.h"

// Estados representados por números
enum State { OnOut = 0, OnOver, OnClick };

class SDLApplication;

class ButtonComponent : public Component {

protected:
	// Función a realizar
	CallBack function;

	// Estado del botón
	int state;

	// Puntero al marco del botón
	GameObject* frame;

	// Punteros a componentes
	Transform* tr;
	Animator* animButton;
	Animator* animFrame;

	// Indice para el ultimo boton seleccionado
	int index;

	bool chest;
public:
	static const int id = _BUTTON;
	ButtonComponent(CallBack _f, GameObject* _frame = nullptr ,int _index = -1, bool chst = false) :
		Component(), state(0), function(_f), frame(_frame), tr(nullptr), animButton(nullptr), animFrame(nullptr), index(_index), chest(chst) {}

	virtual void update();
	virtual void handleInput();
	virtual void initComponent();

	// Comprueba si las coordenadas introducidas están sobre el mouse
	virtual bool isOver(int mouseX, int mouseY);
	// Ejecuta el callback
	virtual void onClick();
	// Actualiza la animación del botón según el estado
	virtual void updateAnimation();

	// Cambia el estado de los animators para mostrar el estado del botón recibido
	void changeStateAnim(string key);
};