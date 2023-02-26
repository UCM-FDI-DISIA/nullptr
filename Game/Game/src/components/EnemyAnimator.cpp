#include "EnemyAnimator.h"

/*
	Se crean animaciones preestablecidas del Player.
	Dependiendo de la velocidad del Player de su Transform,
	se pone la animacion adecuada
*/

// Destructora
EnemyAnimator::~EnemyAnimator() {
	transform = nullptr;
}

// Inicializa el componente
void EnemyAnimator::initComponent() {
	Animator::initComponent();

	transform = gObj->getComponent<Transform>();
	if (gStt != nullptr) {
		createAnim(MELE_ENEMY_MOVE, MELE_ENEMY_MOVE_INITIAL_FRAME, MELE_ENEMY_MOVE_FINAL_FRAME, MELE_ENEMY_MOVE_FRAME_RATE, -1);
		createAnim(MELE_ENEMY_ATACK, MELE_ENEMY_ATACK_INITIAL_FRAME, MELE_ENEMY_ATACK_FINAL_FRAME, MELE_ENEMY_ATACK_FRAME_RATE, -1);


		// Se anima el estado idle por predeterminado
		play(MELE_ENEMY_MOVE);
	}
}

// Actualiza la animacion del Player dependiendo de su velocidad
void EnemyAnimator::update() {
	Animator::update();

	if (transform != nullptr) {
		if (transform->getVel().getX() < 0 || transform->getVel().getX() > 0 || transform->getVel().getY() < 0 || transform->getVel().getY() > 0) {
			if (currentAnimationKey() != MELE_ENEMY_MOVE) {
				play(MELE_ENEMY_MOVE);
			}
		}
		else if (currentAnimationKey() != MELE_ENEMY_ATACK) {
			play(MELE_ENEMY_ATACK);
		}

		if (transform->getVel().getX() > 0) {
			flipNone();
		}
		else if (transform->getVel().getX() < 0) {
			flipHorizontal();
		}
	}
}