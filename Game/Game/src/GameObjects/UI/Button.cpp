#include "Button.h"
#include "../../core/SDLApplication.h"

Button::Button(CallBack _c, SDLApplication* game) : GameObject() {
	addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT / 2 - 18), Vector2D(0, 0), 158, 36);
	addComponent<Image>(game->getTexture("Opciones"));
	//addComponent<Animator>(_ANIMATOR);
	addComponent<ButtonComponent>(_c);
}