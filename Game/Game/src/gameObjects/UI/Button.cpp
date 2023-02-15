#include "Button.h"
#include "../../core/SDLApplication.h"

Button::Button(CallBack _cb, SDLApplication* game, Vector2D _pos, string key, int _w, int _h, int _r, int _c) : GameObject() {
	addComponent<Transform>(_pos, Vector2D(0, 0), 158, 36);
	addComponent<Animator>(game->getTexture(key), _w, _h, _r, _c);
	addComponent<ButtonComponent>(_cb, game);
}