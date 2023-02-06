#pragma once
#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <list>
#include "../core/GameObject.h"

class SDLApplication;
using namespace std;

class GameState {
protected:
    SDLApplication* game = nullptr;
    list<GameObject*> stateScene;

public:
    // Constructor
    GameState(SDLApplication* _game);
    // Destructor
    virtual ~GameState();
    // Updates scene's objects
    virtual void update();
    // Draws the scene on screen
    virtual void render() const;
    // Handles the event
    virtual void handleEvent(SDL_Event event);
};
#endif
