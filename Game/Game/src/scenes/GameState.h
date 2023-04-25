#pragma once
#include <vector>
#include "../gameObjects/GameObject.h"
#include "../gameObjects/General Objects/Camera.h"
#include "../gameObjects/General Objects/Pointer.h"

class SDLApplication;
using namespace std;

class GameState {
protected:
    Camera* camera;
    Pointer* pointer;
    array<std::vector<GameObject*>, maxGroupId> entsByGroup_;
    int lastButtonIndex;
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
    inline Camera* getCamera() const { return camera; }

    // Devuelve el puntero
    inline Pointer* getPointer() const { return pointer; }

    void setLastIndex(int index) { lastButtonIndex = index; }
};
