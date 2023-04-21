#include "Button.h"
#include "../../core/SDLApplication.h"

// Añade los componentes al botón y crea sus animaciones
void Button::initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, int _index, GameObject* _frame) {
	// Transform
	addComponent<Transform>(_pos, Vector2D(), _animInfo.w, _animInfo.h);

	// Animator y sus animaciones
	createButtonAnimations(addComponent<Animator>(SDLApplication::getTexture(_animInfo.key), _animInfo.fw, _animInfo.fh, _animInfo.rows, _animInfo.cols));

	if (_frame != nullptr) createButtonAnimations(_frame->getComponent<Animator>());

	// Componente de botones
	addComponent<ButtonComponent>(_cb, _frame, _index);
}

void Button::initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, GameObject* _frame) {
	initGameObject(_cb, _pos, _animInfo, -1, _frame);
}

// Crea las animaciones esenciales de un bot�n: OnClick, OnOver y Idle
void Button::createButtonAnimations(Animator* animator) {
	animator->attachToCamera();
	animator->createAnim(Constant::getString("ONOUT"), Constant::getInt("ONOUT_ALL_FRAMES"), Constant::getInt("ONOUT_ALL_FRAMES"), Constant::getInt("ONCLICK_ONOUT_SPEED"), -1);
	animator->createAnim(Constant::getString("ONOVER"), Constant::getInt("ONONVER_START_FRAME"), Constant::getInt("ONOVER_END_FRAME"), Constant::getInt("ONOVER_SPEED"), -1);
	animator->createAnim(Constant::getString("ONCLICK"), Constant::getInt("ONCLICK_ALL_FRAMES"), Constant::getInt("ONCLICK_ALL_FRAMES"), Constant::getInt("ONCLICK_ONOUT_SPEED"), -1);
	animator->play(Constant::getString("ONOUT"));
}