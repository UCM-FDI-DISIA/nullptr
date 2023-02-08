#include "MenuButton.h"
#include "Game.h"

// Constructor
MenuButton::MenuButton(Vector2D _position, int _width, int _height, Texture* _texture, Game* _game, CallBack*_function) : Image(_position, _width, _height, _texture), game(_game), currentState(0), nextState(0), isClicked(false), function(_function) {}

// Updates the button image
void MenuButton::update() {
    if (currentState != nextState) {
        currentState = nextState;
    }
    if (isClicked) {
        function(game);
        isClicked = false;
    }
}

// Renders the button state
void MenuButton::render() const {
    texture->renderFrame({(int) position.getX(), (int) position.getY(), width, height}, 0, currentState);
}

// Handles the button state
void MenuButton::handleEvent(SDL_Event event){
    // If mouse left button clicked
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
        if (isOver(event.motion.x, event.motion.y)) {
            nextState = 2;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
        if (isOver(event.motion.x, event.motion.y)) {
            isClicked = true;
        }
    }
    // If mouse cursor is over the button and not clicked
    else if (event.type == SDL_MOUSEMOTION) {
        if (isOver (event.motion.x, event.motion.y)) {
            nextState = 1;
        }
        else if (currentState != 0) nextState = 0;
    }
    else if (currentState != 0) nextState = 0;
}

// Returns if the position given is inside the rectangle of the button
bool MenuButton::isOver(double x, double y) const {
    return x > position.getX()
        && x < position.getX() + width
        && y > position.getY()
        && y < position.getY() + height;
}

// Returns if the button was clicked
bool MenuButton::clicked() const { return isClicked; }