#pragma once
#include <vector>
#include "../gameObjects/GameObject.h"
#include "../gameObjects/General Objects/Camera.h"
#include "../gameObjects/General Objects/Pointer.h"

class SDLApplication;
using namespace std;

class GameState {
protected:
    vector<GameObject*> gObjs;
    Camera* camera;
    Pointer* pointer;
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

    void addGameObject(GameObject* object);
    void refresh();
    //Inserta un nuevo GameObject a la escena
    template<typename T = GameObject, typename ...Ts>
    T* addGameObject(Ts&& ...args) {
        T* e = new T();
        e->setAlive(true);
        e->setContext(this);
        e->initGameObject(std::forward<Ts>(args)...);
        gObjs.push_back(e);
        return e;
    }

    // Devuelve la camara
    Camera* getCamera() const;
};
