#include "Tuto.h"
#include "../../core/SDLApplication.h"
#include "../../core/GameControl.h"

// Inicializa el objeto
void Tuto::initGameObject(Transform* pl) {
	// Componente transaforms
	addComponent<Transform>(Vector2D(WIN_WIDTH - 128 * 2, WIN_HEIGHT - 128 * 2),
		VECTOR_ZERO, COMPANION_WIDTH, COMPANION_HEIGHT);

	// Componente Animator
	myAnim = addComponent<Animator>(SDLApplication::getTexture(COMPANION_TEXTURE),
		COMPANION_SPRITE_WIDTH, COMPANION_SPRITE_HEIGHT, 6, 5);

	// Crear animaciones
	myAnim->createAnim(IDLE, 0, 1, 5, -1);
	// Animaciones con controller
	if (ih().isControllerConnected()) {
		myAnim->createAnim("MovementCtrlls", 15, 16, 5, -1);
		myAnim->createAnim("AimCtrlls", 19, 20, -1);
		myAnim->createAnim("AttackCtrlls", 23, 24, -1);
		myAnim->createAnim("AbilityCtrlls", 27, 28, -1);
	}
	// Animaciones con teclas
	else {
		myAnim->createAnim("MovementCtrlls", 13, 14, 5, -1);
		myAnim->createAnim("AimCtrlls", 17, 18, -1);
		myAnim->createAnim("AttackCtrlls", 21, 22, -1);
		myAnim->createAnim("AbilityCtrlls", 25, 26, -1);
	}

	// Reproducir base
	myAnim->play("MovementCtrlls");

	// Componente lerp
	l = addComponent<LerpComponent>(pl);
}