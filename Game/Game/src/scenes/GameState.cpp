#include "GameState.h"
#include "../core/SDLApplication.h"

// Constructor
GameState::GameState(SDLApplication* _game) : game(_game) {}

// Destructor
GameState::~GameState() {
    for (GameObject* object : stateScene) {
        delete(object);
    }
    for (Manager* manager : sceneManagers) {
        delete(manager);
    }
}

// Updates scene's objects
// Actualiza los objetos de la escea
void GameState::update() {
    for (GameObject* object : stateScene) {
        object->update();
    }
    for (Manager* manager : sceneManagers) {
        manager->update();
    }
}

// Draws the scene on screen
// Dibuja la escena en pantalla
void GameState::render() const {
    for (GameObject* object : stateScene) {
        object->render();
    }
    for (Manager* manager : sceneManagers) {
        manager->render();
    }
}

// Handles the event
// Maneja el evento actual
void GameState::handleEvent(SDL_Event event) {
    for (GameObject* object : stateScene) {
        object->handleEvent(event);
    }
    for (Manager* manager : sceneManagers) {
        manager->handleEvent(event);
    }
}