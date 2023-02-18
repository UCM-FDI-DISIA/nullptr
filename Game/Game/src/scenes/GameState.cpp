#include "GameState.h"
#include "../core/SDLApplication.h"

// Constructor
GameState::GameState(SDLApplication* _game) : gObjs(), game(_game), camera(addGameObject<Camera>()) { 
    gObjs.reserve(100);
}

// Destructor
GameState::~GameState() {
    for (GameObject* gObj : gObjs) {
        delete(gObj);
        gObj = nullptr;
    }
}

// Actualiza los objetos de la escena
void GameState::update() {
    for (GameObject* gObj : gObjs) {
        gObj->update();
    }

    refresh();
}

// Dibuja la escena en pantalla
void GameState::render() const {
    for (GameObject* gObj : gObjs) {
        gObj->render();
    }
}

// Maneja el evento actual
void GameState::handleInput() {
    for (GameObject* gObj : gObjs) {
        gObj->handleInput();
    }
}

// Borra todos los GameObject no vivos
void GameState::refresh() {
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

// Devuelve la camara de la escena
Camera* GameState::getCamera() const { return camera; }