#include "TutorialComponent.h"
#include "../../scenes/TutorialScene.h"
#include "../../core/GameControl.h"

// Constructora
TutorialComponent::TutorialComponent(CallBack callback, vector<pair<CallBack, double>> steps) : 
	activatePopup(callback), startime(SDL_GetTicks()), timeOffset(0), steps(steps),
	current(Movimiento), firstActionDone(false), canCount(true) {}


// Actualiza la escena
void TutorialComponent::update() {
	// Si el jugador ha realizado la accion debida, empieza el contador
	if (canCount) timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
	else setCanCount();

	cout << timeOffset << endl;

	// Si pasa 1 segundo y esta desactivado el popup o si se ha activado la accion y ha pasado su tiempo de delay, se activa
	if ((timeOffset >= 1 && !firstActionDone) || (timeOffset >= steps[current].second && firstActionDone)) {
		activatePopup();
		firstActionDone = true;
		canCount = false;
		timeOffset = 0;
	}
}

void TutorialComponent::setCanCount() {
	
	switch(current){
		case Movimiento:
			if (GameControl::instance()->movementX() || GameControl::instance()->movementY()) canCount = true;
		break;

		case Carta:
			// Si he usado la carta 5 veces
			//if () canCount = true;
		break;

		case Descarte:
			// Si gasto una carta, hablo del sistema de mazo, pila y mano (y le doy su mazo bueno)
			timeOffset = steps[Descarte].second;
		break;

		case Enemigos:
			// Si el enemigo muere, timeOffSet = steps[Enemigos].second 
		break;

		case Habilidad:
			// Si el jugador realiza la accion de habilidad, empezar a contar
		break;

		case Drops:
			// Si un enemigo muere, espero 2 segundos para hablar de los drops
			break;

		case Portal:
			// Si el portal llega a 100 %, muestro el popUp
		break;
	}
}