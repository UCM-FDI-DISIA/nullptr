#ifndef GAME_STATE_MACHINE_H_
#define GAME_STATE_MACHINE_H_
#include <stack>
#include "../scenes/GameState.h"
using namespace std;

class GameStateMachine {
private:
    stack<GameState*> gameStates;
    stack<GameState*> gameStatesToErase;
public:
    // Constructor
    GameStateMachine();
    // Destructor
    ~GameStateMachine();
    // Adds state
    void pushState(GameState* newState);
    // Erases state
    void popState();
    // Erases every state on the stack
    void clearStates();
    // Return current state
    GameState* currentState();
    // Changes the current state
    void changeState(GameState* newState);
    // Clears the game states to erase stack
    void clearStatesToErase();
};
#endif
