#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <SDL.h>
#include "ecs.h"
class GameObject;
class Manager;

class Component {
protected:
	GameObject* gObj;
	Manager* mngr;
public:
	// Constructor
	Component() : gObj(nullptr), mngr(nullptr) {}
	// Destructor
	virtual ~Component() {}
	// Sets the GameObject and the Manager of the Component
	// Asigna el GameObject y el Manager del Component
	inline void setContext(GameObject* _gObj, Manager* _mngr) {
		gObj = _gObj;
		mngr = _mngr;
	}
	// Inizializes Component if it's necessary
	// Inicializa el Component si es necesario
	virtual void initComponent() {}
	// Updates the Component
	// Actualiza el Component
	virtual void update() {}
	// Draws the Component on screen
	// Dibuja el Component en pantalla
	virtual void render() const {}
	// Handle's the Component's events
	// Maneja los eventos del Component
	virtual void handleEvent(SDL_Event event) {}
};

#endif // !COMPONENT_H_
