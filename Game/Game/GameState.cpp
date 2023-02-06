#include "GameState.h"
#include "Game.h"

// Constructor
GameState::GameState(Game* _game) : game(_game) {}

// Destructor
GameState::~GameState() {
    for (GameObject* object : stateScene) {
        delete(object);
    }
}

// Updates scene's objects
void GameState::update() {
    for (GameObject* object : stateScene) {
        object->update();
    }
}

// Draws the scene on screen
void GameState::render() const {
    for (GameObject* object : stateScene) {
        object->render();
    }
}

// Handles the event
void GameState::handleEvent(SDL_Event event) {
    for (EventHandler* object : eventHandlers) {
        object->handleEvent(event);
    }
}