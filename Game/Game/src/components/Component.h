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
	// Constructora
	Component() : gObj(nullptr), mngr(nullptr) {}
	// Destructora
	virtual ~Component() {}
	// Asigna el GameObject y el Manager del Component
	inline void setContext(GameObject* _gObj, Manager* _mngr) {
		gObj = _gObj;
		mngr = _mngr;
	}
	// Inicializa el Component si es necesario
	virtual void initComponent() {}
	// Actualiza el Component
	virtual void update() {}
	// Dibuja el Component en pantalla
	virtual void render() const {}
	// Maneja los eventos del Component
	virtual void handleInput() {}
};

#endif // !COMPONENT_H_
