#pragma once
#ifndef MANAGER_H_
#define MANAGER_H_

#include "GameObject.h"

class Manager {
private:
	std::vector<GameObject*> gObjs;
public:
	// Constructor
	Manager();
	// Destructor
	virtual ~Manager();
	// Adds a new empty GameObject to the Manager, returns a pointer to said GameObject
	// Añade un nuevo GameObject vacío al Manager, devuelve un puntero a dicho GameObject
	GameObject* addGameObject();
	// Erases every not alive GameObject
	// Borra todos los GameObject no vivos
	void refresh();
	// Updates every GameObject of the Manager
	// Actualiza todos los GameObject del Manager
	void update();
	// Draws on screen every GameObject of the Manager
	// Dibuja en pantalla todos los GameObject del Manager
	void render() const;
	// Handle's the  current event for every GameObject of the Manager
	// Maneja el evento actual para todos los GameObject del Manager
	void handleEvent(SDL_Event event);
};

#endif // !MANAGER_H_
