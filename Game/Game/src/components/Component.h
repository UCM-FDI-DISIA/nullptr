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
	inline void setContext(GameObject* _gObj, Manager* _mngr) {
		gObj = _gObj;
		mngr = _mngr;
	}
	// Inizializes component if it's necessary
	virtual void initComponent() {}
	// Updates the Component
	virtual void update() {}
	// Draws the Component on screen
	virtual void render() {}
	// Handle's the Component's events
	virtual void handleEvent(SDL_Event event) {}
};

#endif // !COMPONENT_H_
