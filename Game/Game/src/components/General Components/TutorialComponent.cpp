#include "TutorialComponent.h"
#include "../../scenes/TutorialScene.h"
#include "../../core/GameControl.h"

// Constructora
TutorialComponent::TutorialComponent(CallBack callback, vector<pair<CallBack, double>> steps) : 
	activatePopup(callback), timeOffset(0), steps(steps),
	current(Introduccion), firstActionDone(false), canCount(true), discarted(false) {}


// Actualiza la escena
void TutorialComponent::update() {
	if (canCount) timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
	changeState();
}

void TutorialComponent::changeState() {
	
	switch(current){
		case Introduccion:
			if (timeOffset >= 1.5) {
				activatePopup();		// Con el texto de movimiento
				timeOffset = 0;
				current = Movimiento;
				canCount = false;
			}
		break;

		case Movimiento:
			if (!canCount) canCount = GameControl::instance()->movementX() != 0 || GameControl::instance()->movementY() != 0;
			else if (canCount && timeOffset >= 5){
				activatePopup();		// Con el texto de la carta
				timeOffset = 0;
				current = Carta;
				canCount = false;
			}

		break;

		case Carta:
			// Si he usado la carta 5 veces
			if (discarted) {
				activatePopup();		// Con el texto de descartar
				current = Descarte;
			}
		break;

		case Descarte:
			// Si gasto una carta, hablo del sistema de mazo, pila y mano (y le doy su mazo bueno)
			
		break;

		case Enemigos:
			// Si el enemigo muere, timeOffSet = steps[Enemigos].second
			cout << "ESTAS EN EL PASO DE ENEMIGOS" << endl;
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