#include "GameStateMachine.h"

// Constructor
GameStateMachine::GameStateMachine() {}

// Destructor
GameStateMachine::~GameStateMachine() {
    clearStates();
    clearStatesToErase();
}

// Adds state
void GameStateMachine::pushState(GameState* newState) { gameStates.push(newState); }

// Erases state
void GameStateMachine::popState() {
    gameStatesToErase.push(gameStates.top());
    gameStates.pop(); 
}

// Erases every state on the stack
void GameStateMachine::clearStates() {
    while (!gameStates.empty()) popState();
}

// Return current state
GameState* GameStateMachine::currentState() { return gameStates.top(); }

// Changes the current state
void GameStateMachine::changeState(GameState* newState) {
    clearStates();
    pushState(newState);
}

// Clears the game states to erase stack
void GameStateMachine::clearStatesToErase() {
    while (!gameStatesToErase.empty()){
        delete(gameStatesToErase.top());
        gameStatesToErase.pop();
    }
}