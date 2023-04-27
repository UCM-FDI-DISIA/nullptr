#include "TutorialComponent.h"
#include "../../scenes/TutorialScene.h"
#include "../../core/GameControl.h"

// Constructora
TutorialComponent::TutorialComponent(TutorialScene* _t) : ts(_t), startime(SDL_GetTicks()), timeOffset(0) {}

// Inicializa el componente
void TutorialComponent::initComponent() {
	current = Movimiento;
}

// Actualiza la escena
void TutorialComponent::update() {
	timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();

	if (timeOffset >= 4) {
		ts->activatePopUp();
	}
}