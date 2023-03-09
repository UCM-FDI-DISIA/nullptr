#pragma once
#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <list>
#include "../gameObjects/GameObject.h"
#include "../gameObjects/General Objects/Camera.h"

class SDLApplication;
using namespace std;

class GameState {
protected:
    Camera* camera = nullptr;
    std::array<std::vector<GameObject*>, maxGroupId> entsByGroup_;
public:
    // Constructor
    GameState();
    // Destructor
    virtual ~GameState();
    // Actualiza los objetos de la escea
    virtual void update();
    // Dibuja la escena en pantalla
    virtual void render() const;
    // Maneja el evento actual
    virtual void handleInput();
    // Borra todos los GameObject no vivos

    void refresh();
    //Inserta un nuevo GameObject a la escena indicando su grupo
    template<typename T = GameObject, typename ...Ts>
    T* addGameObject(grpId group, Ts&& ...args) {
        T* e = new T();
        e->setAlive(true);
        e->setContext(this, group);
        e->initGameObject(std::forward<Ts>(args)...);
        entsByGroup_[group].push_back(e);
        return e;
    }
    //Inserta un nuevo GameObject a la escena en el grupo General
    template<typename T = GameObject, typename ...Ts>
    T* addGameObject(Ts&& ...args) {
        return addGameObject<T>(_grp_GENERAL, std::forward<Ts>(args)...);
    }
    // Devuelve una lista con el grupo seleccionado
    inline const vector<GameObject*>& getEntitiesByGroup(grpId_type gId) {
        return entsByGroup_[gId];
    }

    // Devuelve la camara
    Camera* getCamera() const;
};
#endif
