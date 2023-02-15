#pragma once
#include "Component.h"
#include "Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Animator.h"
#include "../GameObjects/UI/Button.h"

// Estados representados por números
enum State { OnOut = 0, OnOver, OnClick };

class SDLApplication;
typedef void CallBack(SDLApplication* game);

class ButtonComponent : public Component {

private:
	// Puntero al juego
	SDLApplication* game;
	
	// Función a realizar
	CallBack* function;

	// Estado del botón
	int state;

	// Puntero al marco del botón -> de no tener, debe ser "nullptr"
	GameObject* frame;

	// Punteros a componentes
	Transform* tr;
	Animator* animButton;
	Animator* animFrame;

public:
	static const int id = _BUTTON;
	ButtonComponent(CallBack* _f, SDLApplication* _g, GameObject* _frame) : Component(), state(0), function(_f), game(_g), frame(_frame) {}

	virtual void update();
	virtual void handleInput();
	virtual void initComponent();

	void changeStateAnim(string key);
};