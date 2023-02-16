#include "GameState.h"
#include "../core/SDLApplication.h"

// Constructor
GameState::GameState(SDLApplication* _game) : game(_game), camera(new Camera()) { stateScene.push_back(camera); }

// Destructor
GameState::~GameState() {
    

    for (GameObject* object : stateScene) {
        delete(object);
    }
    for (Manager* manager : sceneManagers) {
        delete(manager);
    }
}

// Actualiza los objetos de la escena
void GameState::update() {
    for (GameObject* object : stateScene) {
        object->update();
    }
    for (Manager* manager : sceneManagers) {
        manager->update();
    }

    refresh();
}

// Dibuja la escena en pantalla
void GameState::render() const {
    for (GameObject* object : stateScene) {
        object->render();
    }
    for (Manager* manager : sceneManagers) {
        manager->render();
    }
}

// Maneja el evento actual
void GameState::handleInput() {
    for (GameObject* object : stateScene) {
        object->handleInput();
    }
    for (Manager* manager : sceneManagers) {
        manager->handleInput();
    }
}

// Borra todos los GameObject no vivos
void GameState::refresh() {
    for (Manager* manager : sceneManagers) {
        manager->refresh();
    }
    stateScene.erase(
        std::remove_if(stateScene.begin(), stateScene.end(), [](GameObject* e) {
            if (e->isAlive()) {
                return false;
            }
            else {
                delete e;
                return true;
            }
            }), //
        stateScene.end());
}

// Devuelve la camara de la escena
Camera* GameState::getCamera() const { return camera; }