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

	// Cartas
	if (!crdComp_->isLocked()) {
		// Ataque
		if (canAttack) {
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
		// Selección carta
		if (gmCtrl_.selectRightCard()) {
			crdComp_->selectRight();
		}
		else if (gmCtrl_.selectLeftCard()) {
			crdComp_->selectLeft();
		}
		// Téclas numéricas
		if (!gmCtrl_.controllerActive()) {

			if (InputHandler::instance()->isKeyJustDown(SDLK_1)) {
				crdComp_->switchActive(0);
			}
			else if (InputHandler::instance()->isKeyJustDown(SDLK_2)) {
				crdComp_->switchActive(1);
			}
			else if (InputHandler::instance()->isKeyJustDown(SDLK_3)) {
				crdComp_->switchActive(2);
			}
			else if (InputHandler::instance()->isKeyJustDown(SDLK_4)) {
				crdComp_->switchActive(3);
			}
		}
	}
	// Cursor
	gmCtrl_.controllerToCursor();
	// Portal
	if (canExit && gmCtrl_.completeLevel()) {
		prtlComp_->countDownSetup();
	}
	// Pausa
	if (gmCtrl_.pause()) {
		SDLApplication::pauseGame();
	}
}


void PlayerInputComponent::setPortalComponent(ChargedPortalComponent* prtlC) { prtlComp_ = prtlC; }