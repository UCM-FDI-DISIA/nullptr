#include "PlayerInputComponent.h"
#include "../../core/SDLApplication.h"
#include "../../scenes/BattleScene.h"
#include "../General Components/ChargedPortalComponent.h"
#include "../../scenes/TutorialScene.h"

void PlayerInputComponent::initComponent() {
	plMovement_ = gObj->getComponent<PlayerMovementComponent>();
	crdComp_ = gObj->getComponent<CardComponent>();
}

void PlayerInputComponent::handleInput() {
	// Movimiento
	if (canMove) plMovement_->setDirection(Vector2D(gmCtrl_.movementX(), gmCtrl_.movementY()));
	// Ataque
	if (canAttack && !crdComp_->getLocked()) {
		if (gmCtrl_.basic()) {
			crdComp_->attack();
		}
		if (canUseAbility && gmCtrl_.ability()) {
			crdComp_->ability();
			if (tutorial) {
				dynamic_cast<TutorialScene*>(gStt)->notifyAbility();
				tutorial = false;
			}
		}
	}
	// Cursor
	gmCtrl_.controllerToCursor();
	// Selección carta
	if (gmCtrl_.selectRightCard()) {
		crdComp_->selectRight();
	}
	else if (gmCtrl_.selectLeftCard()) {
		crdComp_->selectLeft();
	}
	// Portal
	if (canExit && gmCtrl_.completeLevel()) {
		prtlComp_->countDownSetup();
	}
	if (ih().isKeyDown(SDLK_LESS)) {
		prtlComp_->debugCountDownSetup();
	}

	// Pausa
	if (gmCtrl_.pause()) {
		SDLApplication::pauseGame();
	}
}


void PlayerInputComponent::setPortalComponent(ChargedPortalComponent* prtlC) { prtlComp_ = prtlC; }