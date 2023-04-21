#include "CharacterAnimator.h"

// Constructora, recibe animaciones de idle y movimiento
CharacterAnimator::CharacterAnimator(Texture* _texture, int _w, int _h, int _r, int _c, Animation idle, Animation move) :
	Animator(_texture, _w, _h, _r, _c), wantToAdjustDirection(true) {
	createAnim(Constant::getString("CHARACTER_IDLE_KEY"), idle);
	createAnim(Constant::getString("CHARACTER_MOVE_KEY"), move);
}

// Actualiza la animacion del personaje en funci�n a sus acciones
void CharacterAnimator::update() {
	updatePlayingAnimation();
	Animator::update();
	if (wantToAdjustDirection) adjustDirection();
}


// Actualiza a la animaci�n correspondiente a la acci�n actual, devuelve si ha cambiado de animaci�n o no
bool CharacterAnimator::updatePlayingAnimation() {
	for (auto& action : actions) {
		if (action.second()) return playDiff(action.first);
	}
	if (moving()) return playDiff(Constant::getString("CHARACTER_MOVE_KEY"));
	if (idling()) return playDiff(Constant::getString("CHARACTER_IDLE_KEY"));
	return false;
}


// A�ade una nueva animaci�n que iniciar� cuando el callback pasado devuelva true
void CharacterAnimator::addAction(string key, Animation anim, BoolCallBack cb) {
	createAnim(key, anim);
	actions[key] = cb;
}
// A�ade animaci�n de ataque que iniciar� cuando el callback pasado devuelva true
void CharacterAnimator::addAttack(Animation anim, BoolCallBack cb) {
	addAction(Constant::getString("CHARACTER_ATTACK_IDLE_KEY"), anim, cb);
}


// Devuelve si la acci�n del jugador es idle, siempre se comprueba la �ltima
bool CharacterAnimator::idling() {
	return true;
}

// Devuelve si la acci�n del jugador es movimiento, siempre se coprueba justo antes de idling
bool CharacterAnimator::moving() {
	return (transform->getVel().getX() < 0 ||
		transform->getVel().getX() > 0 ||
		transform->getVel().getY() < 0 ||
		transform->getVel().getY() > 0);
}


// Si el jugador se mueve a la izquierda hace flip horizontal y viceversa
void CharacterAnimator::adjustDirection() {
	if (transform->getVel().getX() > 0) {
		flipNone();
	}
	else if (transform->getVel().getX() < 0) {
		flipHorizontal();
	}
}
