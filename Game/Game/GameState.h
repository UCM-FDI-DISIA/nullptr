#ifndef GAME_STATE_H_
#define GAME_STATE_H_
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
#include "constants.h"
class Game;
using namespace std;

class GameState {
protected:
    Game* game = nullptr;
    list<GameObject*> stateScene;
    list<EventHandler*> eventHandlers;

public:
    // Constructor
    GameState(Game* _game);
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
