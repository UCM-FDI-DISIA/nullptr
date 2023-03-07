#include "PlayerAnimator.h"

/*
	Se crean animaciones preestablecidas del Player.
	Dependiendo de la velocidad del Player de su Transform,
	se pone la animacion adecuada
*/
/*
// Inicializa el componente
void PlayerAnimator::initComponent() {
	Animator::initComponent();

	transform = gObj->getComponent<Transform>();
	if (gStt != nullptr) {
		createAnim(PLAYER_IDLE, PLAYER_IDLE_INITIAL_FRAME, PLAYER_IDLE_FINAL_FRAME, PLAYER_IDLE_FRAME_RATE, -1);
		createAnim(PLAYER_MOVE, PLAYER_MOVE_INITIAL_FRAME, PLAYER_MOVE_FINAL_FRAME, PLAYER_MOVE_FRAME_RATE, -1);

		// Se anima el estado idle por predeterminado
		play(PLAYER_IDLE);
	}
}
*/