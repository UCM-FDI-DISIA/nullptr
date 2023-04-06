#include "GameState.h"
#include "../core/SDLApplication.h"

// Constructor
GameState::GameState() : entsByGroup_() { 
    
    for (auto & grpEnts : entsByGroup_) {
        grpEnts.reserve(100); //Reserva espacio para cada lista
    }
    camera = addGameObject<Camera>();
    pointer = addGameObject<Pointer>(_grp_POINTER);
}

// Destructor
GameState::~GameState() {
    for (auto& group : entsByGroup_) {
        for (auto& e : group) {
            delete e;
            e = nullptr;
        }
    }
}

// Actualiza los objetos de la escena
void GameState::update() {
    for (auto& group : entsByGroup_) {
        for (auto e : group) {
            e->update();
        }
    }

    refresh();
}

// Dibuja la escena en pantalla
void GameState::render() const {
    for (auto& group : entsByGroup_) {
        for (auto e : group) {
            e->render();
        }
    }
}

// Maneja el evento actual
void GameState::handleInput() {
    for (auto& group : entsByGroup_) {
        for (auto e : group) {
            e->handleInput();
        }
    }
}

// Borra todos los GameObject no vivos
void GameState::refresh() {

    for (grpId_type gId = 0; gId < maxGroupId; gId++) {
        auto& grpEnts = entsByGroup_[gId];
        grpEnts.erase(
            std::remove_if(grpEnts.begin(), grpEnts.end(),
                [](GameObject* e) {
                    if (e->isAlive()) {
                        return false;
                    }
                    else {
                        delete e;
                        return true;
                    }
                }),
            grpEnts.end());
    }
}


// Devuelve la camara de la escena
Camera* GameState::getCamera() const { return camera; }
