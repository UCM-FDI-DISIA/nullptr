#include "Button.h"
#include "../../core/SDLApplication.h"

// Añade los componentes al botón y crea sus animaciones
void Button::initGameObject(CallBack _cb, SDLApplication* game, Vector2D _pos, string key, int _w, int _h, int _fw, int _fh, int _r, int _c, GameObject* _frame) {
	// Transform
	addComponent<Transform>(_pos, VECTOR_ZERO, _w, _h);

	// Animator y sus animaciones
	createButtonAnimations(addComponent<Animator>(SDLApplication::getTexture(key), _fw, _fh, _r, _c));

	if (_frame != nullptr) createButtonAnimations(_frame->getComponent<Animator>());

	// Componente de botones
	addComponent<ButtonComponent>(_cb, SDLApplication::instance(), _frame);
}

// Crea las animaciones esenciales de un bot�n: OnClick, OnOver y Idle
void Button::createButtonAnimations(Animator* animator) {
	animator->createAnim(ONOUT, ONOUT_ALL_FRAMES, ONOUT_ALL_FRAMES, ONCLICK_ONOUT_SPEED, -1);
	animator->createAnim(ONOVER, ONONVER_START_FRAME, ONOVER_END_FRAME, ONOVER_SPEED, -1);
	animator->createAnim(ONCLICK, ONCLICK_ALL_FRAMES, ONCLICK_ALL_FRAMES, ONCLICK_ONOUT_SPEED, -1);
	animator->play(ONOUT);
}