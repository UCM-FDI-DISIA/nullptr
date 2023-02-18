#pragma once
#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <list>
#include "../core/GameObject.h"
#include "../core/Manager.h"
#include "../gameObjects/Camera.h"

class SDLApplication;
using namespace std;

class GameState {
protected:
    SDLApplication* game = nullptr;
    list<GameObject*> stateScene;
    list<Manager*> sceneManagers;
    Camera* camera = nullptr;
public:
    // Constructor
    GameState(SDLApplication* _game);
    // Destructor
    virtual ~GameState();
    // Updates scene's objects
    // Actualiza los objetos de la escea
    virtual void update();
    // Draws the scene on screen
    // Dibuja la escena en pantalla
    virtual void render() const;
    // Handles the current event
    // Maneja el evento actual
    virtual void handleInput();
    // Erases every not alive GameObject
    // Borra todos los GameObject no vivos
    void refresh();
    //Add a new GameObject to the scene
    //Inserta un nuevo GameObject a la escena
    void addGameObject(GameObject* toAdd);

    SDLApplication* getGame() const;

    // Devuelve la camara
    Camera* getCamera() const;
};
#endif
