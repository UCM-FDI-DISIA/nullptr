#include "Manager.h"

// Constructor
Manager::Manager() : gObjs() {
	gObjs.reserve(100);
}

// Destructor
Manager::~Manager() {
	for (GameObject* gObj : gObjs) {
		delete gObj;
		gObj = nullptr;
	}
}

// Adds a new empty GameObject to the manager, returns a pointer to said GameObject
// Añade un nuevo GameObject vacío al Manager, devuelve un puntero a dicho GameObject
GameObject* Manager::addGameObject() {
	GameObject* e = new GameObject();
	e->setAlive(true);
	e->setContext(this);
	gObjs.push_back(e);
	return e;
}
void Manager::addGameObject(GameObject* g) {
	g->setAlive(true);
	g->setContext(this);
	gObjs.push_back(g);
}

// Erases every not alive GameObject
// Borra todos los GameObject no vivos
void Manager::refresh() {
	gObjs.erase(
		std::remove_if(gObjs.begin(), gObjs.end(), [](GameObject* e) {
			if (e->isAlive()) {
				return false;
			}
			else {
				delete e;
				return true;
			}
			}), //
		gObjs.end());
}

// Updates every GameObject of the Manager
// Actualiza todos los GameObject del Manager
void Manager::update() {
	for (GameObject* gObj : gObjs) {
		gObj->update();
	}
}

// Draws on screen every GameObject of the Manager
// Dibuja en pantalla todos los GameObject del Manager
void Manager::render() const {
	for (GameObject* gObj : gObjs) {
		gObj->render();
	}
}


// Handle's the  current event for every GameObject of the Manager
// Maneja el evento actual para todos los GameObject del Manager
void Manager::handleInput() {
	for (GameObject* gObj : gObjs) {
		gObj->handleInput();
	}
}