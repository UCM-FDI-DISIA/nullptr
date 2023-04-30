#include "Tuto.h"
#include "../../core/SDLApplication.h"
#include "../../core/GameControl.h"

// Inicializa el objeto
void Tuto::initGameObject(Transform* pl) {
	// Componente transaforms
	tr = addComponent<Transform>(Vector2D(WIN_WIDTH - 128 * 2, WIN_HEIGHT - 128 * 2),
		VECTOR_ZERO, COMPANION_WIDTH, COMPANION_HEIGHT);

	// Componente Animator
	myAnim = addComponent<Animator>(SDLApplication::getTexture(COMPANION_TEXTURE),
		COMPANION_SPRITE_WIDTH, COMPANION_SPRITE_HEIGHT, 8, 5);

	// Crear animaciones
	myAnim->createAnim(IDLE, 0, 1, 5, -1);
	// Animaciones con controller
	if (ih().isControllerConnected()) {
		myAnim->createAnim("MovementCtrlls", 25, 26, 5, -1);
		myAnim->createAnim("AimCtrlls", 27, 28, -1);
		myAnim->createAnim("AttackCtrlls", 29, 30, 5, -1);
		myAnim->createAnim("AbilityCtrlls", 31, 32, 5, -1);
		myAnim->createAnim("ChangeCtrlls", 33, 34, 5, -1);
		myAnim->createAnim("PortalCtrlls", 35, 36, 5, -1);
	}
	// Animaciones con teclas
	else {
		myAnim->createAnim("MovementCtrlls", 13, 14, 5, -1);
		myAnim->createAnim("AimCtrlls", 15, 16, 5, -1);
		myAnim->createAnim("AttackCtrlls", 17, 18, 5, -1);
		myAnim->createAnim("AbilityCtrlls", 19, 20, 5, -1);
		myAnim->createAnim("ChangeCtrlls", 21, 22, 5, -1);
		myAnim->createAnim("PortalCtrlls", 23, 24, 5, -1);
	}

	// Reproducir base
	myAnim->play("MovementCtrlls");

	// Componente lerp
	l = addComponent<LerpComponent>(pl);
}

void Tuto::changeAnim(int c) {
	if (c == 1 || c == 2 || c == 3 || current == 5) myAnim->play("AimCtrlls");
	else if (c == 4) myAnim->play("AbilityCtrlls");
	else if (c == 6) myAnim->play("PortalCtrlls");
	current = c;
}

void Tuto::update() {
	GameObject::update();

	time += SDLApplication::instance()->getDeltaTimeSeconds();
	if (current == 1) {
		if (myAnim->isPlaying("AimCtrlls") && time > 2) {
			myAnim->play("AttackCtrlls");
		}
		else if (myAnim->isPlaying("AttackCtrlls") && time > 4) {
			myAnim->play("AimCtrlls");
			time = 0;
		}
	}
	else if (current == 2 || current == 3) {
		if (myAnim->isPlaying("AimCtrlls") && time > 2) {
			myAnim->play("AttackCtrlls");
		}
		else if (myAnim->isPlaying("AttackCtrlls") && time > 4) {
			myAnim->play("ChangeCtrlls");
		}
		else if (myAnim->isPlaying("ChangeCtrlls") && time > 6) {
			myAnim->play("AimCtrlls");
			time = 0;
		}
	}
	else if (current == 4) {
		if (myAnim->isPlaying("AbilityCtrlls") && time > 2) {
			myAnim->play("ChangeCtrlls");
		}
		else if (myAnim->isPlaying("ChangeCtrlls") && time > 4) {
			myAnim->play("AbilityCtrlls");
			time = 0;
		}
	}
	else if (current == 5) {
		if (myAnim->isPlaying("AimCtrlls") && time > 3) {
			myAnim->play("AttackCtrlls");
		}
		else if (myAnim->isPlaying("AttackCtrlls") && time > 6) {
			myAnim->play("ChangeCtrlls");
		}
		else if (myAnim->isPlaying("ChangeCtrlls") && time > 9) {
			myAnim->play("AbilityCtrlls");
		}
		else if (myAnim->isPlaying("AbilityCtrlls") && time > 12) {
			myAnim->play("AimCtrlls");
			time = 0;
		}
	}
}