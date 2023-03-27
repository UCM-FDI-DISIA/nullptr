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
	Animator* animButton;
	Animator* animFrame;
	int index;

	//Sonidos de los botones
	SoundEffect* hoverOverSound;
	SoundEffect* clickSound;

	vector<SoundEffect*> soundEffects;
public:
	static const int id = _BUTTON;
	ButtonComponent(CallBack _f, GameObject* _frame = nullptr ,int _index = -1) :
		Component(), state(0), function(_f), frame(_frame), tr(nullptr), animButton(nullptr), animFrame(nullptr), index(_index) {}

	virtual void update();
	virtual void handleInput();
	virtual void initComponent();

	// Comprueba si las coordenadas introducidas están sobre el mouse
	virtual bool isOver(int mouseX, int mouseY);
	// Ejecuta el callback
	virtual void onClick();
	// Actualiza la animación del botón según el estado
	virtual void updateAnimation();

	// Cambia el estado de los animators para mostrar el estado del bot�n recibido
	void changeStateAnim(string key, int state);
};