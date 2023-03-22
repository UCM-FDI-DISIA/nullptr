#include "ChargedPortalComponent.h"

ChargedPortalComponent::ChargedPortalComponent(vector<GameObject*>& nums) : Component(), 
							numbers(nums), exit(false), deltaTime(0) {}

void ChargedPortalComponent::initComponent() {
	brComp = gObj->getComponent<BarComponent>();
}

void ChargedPortalComponent::update() {
	if (exit) {
		// Si no se ha empezado a contar y se pulsa la p, empezar la cuenta atrás
		if (InputHandler::instance()->isKeyJustDown(SDLK_p) && deltaTime == 0) countDownSetup();
		else {
			// Si ya se ha empezado la cuenta atrás
			if (deltaTime != 0) {
				// Sumar al contador y reflejar cambios en el número
				deltaTime += SDLApplication::instance()->getDeltaTimeSeconds();
				brComp->changeEtherNumbers(countDownNumber, 5 - (int)deltaTime);

				// Salir al menú principal si han pasad 5.6 secs (5 de mostrar del 5 al 1 y 0.6 del 0)
				if (deltaTime > COUNTDOWN_TIME) SDLApplication::returnToMapScene();
			}
		}
	}
}

// Activar la salida para que el update empiece a recoger input
void ChargedPortalComponent::activateExit() {
	exit = true;
}

// Prepara el contador y el número para la cuenta atrás
void ChargedPortalComponent::countDownSetup() {
	// Empezar el contador
	deltaTime += SDLApplication::instance()->getDeltaTimeSeconds();

	// Guardar el primer número del vector y borrar el resto
	countDownNumber = numbers[0];
	for (int i = N_ETHER_COUNTER - 1; i > 0; i--) numbers[i]->setAlive(false);

	// Reposicionar el número
	Transform* tr = countDownNumber->getComponent<Transform>(); 
	tr->setPos(UI_COUNTDOWN_ETHER_POS);
	tr->setWidth(tr->getWidth() * 1.5);
	tr->setHeight(tr->getHeight() * 1.5);
}