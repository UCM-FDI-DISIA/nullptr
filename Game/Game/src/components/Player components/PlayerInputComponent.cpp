#include "PlayerInputComponent.h"
#include "../../core/SDLApplication.h"
#include "../../scenes/BattleScene.h"
#include "../General Components/ChargedPortalComponent.h"

void PlayerInputComponent::initComponent() {
	plMovement_ = gObj->getComponent<PlayerMovementComponent>();
	crdComp_ = gObj->getComponent<CardComponent>();
}

void PlayerInputComponent::handleInput() {
	// Movimiento
	plMovement_->setDirection(Vector2D(gmCtrl_.movementX(), gmCtrl_.movementY()));
	// Ataque
	if (!crdComp_->getLocked()) {
		if (gmCtrl_.basic()) {
			crdComp_->attack();
		}
		if (gmCtrl_.ability()) {
			crdComp_->ability();
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
	if (gmCtrl_.completeLevel()) {
		prtlComp_->countDownSetup();
	}
	// Pausa
	if (gmCtrl_.pause()) {
		SDLApplication::pauseGame();
	}
}


void PlayerInputComponent::setPortalComponent(ChargedPortalComponent* prtlC) { prtlComp_ = prtlC; }