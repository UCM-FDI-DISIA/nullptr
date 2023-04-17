#include "GameState.h"
#include "../core/SDLApplication.h"

// Constructor
GameState::GameState() : entsByGroup_(), butNavigator(new ButtonNavigator()), gmCtrl_(gmCtrl()) { 
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
    delete butNavigator;
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

// Devuelve el navegador entre botones
ButtonNavigator* GameState::getButtonNavigator() const { return butNavigator; }

// Crear un botón especificado en la escena
Button* GameState::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
    AnimatorInfo aI = AnimatorInfo(key);
    // Crear marco
    GameObject* frame = addGameObject();
    frame->addComponent<Transform>(_fPos, Vector2D(), MM_BUTTONFRAME_WIDTH, MM_BUTTONFRAME_HEIGHT);
    frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols);

    // Crear bot�n
    return addGameObject<Button>(_cb, _bPos, aI, frame);
}