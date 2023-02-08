#ifndef MENUBUTTON_H_
#define MENUBUTTON_H_
#include "Image.h"
#include "EventHandler.h"
class Game;

typedef void CallBack(Game* game);

class MenuButton : public Image, public EventHandler {
private:
    Game* game = nullptr;
    int currentState, nextState;
    bool isClicked;
    CallBack* function;

public:
    // Constructor
    MenuButton(Vector2D _position, int _width, int _height, Texture* _texture, Game* _game, CallBack* _function);
    // Updates the button image
    virtual void update();
    // Renders the button state
    virtual void render() const;
    // Handles the button state
    virtual void handleEvent(SDL_Event event);
    // Returns if the position given is inside the rectangle of the button
    bool isOver(double x, double y) const;
    // Returns if the button was clicked
    bool clicked() const;
};
#endif
