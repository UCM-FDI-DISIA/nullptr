#include "Button.h"
#include "../../core/SDLApplication.h"

Button::Button(CallBack _c, SDLApplication* game, Vector2D _pos) : GameObject() {
	addComponent<Transform>(_pos, Vector2D(0, 0), 158, 36);
	addComponent<Image>(game->getTexture("Opciones"));
	//addComponent<Animator>(_ANIMATOR);
	addComponent<ButtonComponent>(_c, game);
}