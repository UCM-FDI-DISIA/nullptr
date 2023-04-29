#include "TutorialComponent.h"
#include "../../scenes/TutorialScene.h"
#include "../../core/GameControl.h"

// Constructora
TutorialComponent::TutorialComponent(CallBack callback, vector<pair<CallBack, double>> steps) : 
	activatePopup(callback), timeOffset(0), steps(steps),
	current(Introduccion), firstActionDone(false), canCount(true), discarted(false), newHand(false), 
	ability(false), canAdvance(false), ts(nullptr) {}


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
				activatePopup();		// Hablo del sistema de mazo, pila y mano (y le doy su mazo bueno)
				current = Mano;
				discarted = false;
			}
		break;

		case Mano:
			// Le doy un tiempo para q siga usando cartas y viendo como se descartan y vuelven, hasta que use una mano entera
			if (newHand) {
				activatePopup();		// Con el texto de enemigos
				current = Enemigos;
				newHand = false;
				ts = dynamic_cast<TutorialScene*>(gStt);
				timeOffset = 0;
				canAdvance = false;
			}
		break;

		case Enemigos:
			// Hasta q no mate al enemigo
			if (canAdvance) {
				canCount = ts->getTestEnemy();
				if (timeOffset >= 1) {
					activatePopup();		// Con el texto de como se usan las habilidades
					current = Habilidad;
					timeOffset = 0;
					canCount = false;
					canAdvance = false;
				}
			}
		break;

		case Habilidad:
			// Si el jugador realiza la accion de habilidad, empezar a contar
			if (canAdvance) {
				canCount = ability;
				if (timeOffset >= 1.5) {
					activatePopup();		// Con el texto "Las habilidades gastan mana, y ese mana se consigue.."
					current = Drops;
					canCount = false;
					timeOffset = 0;
					canAdvance = false;
				}
			}
		break;

		case Drops:
			// Si ya no hay enemigo, y recojo todo el mana
			if (canAdvance && ts->getTestEnemy() && ts->getManaNumber()) {
				activatePopup();		// Con el texto de "Los enemigos tambien dejan eter, sirve para pasar el nivel)
				current = Portal;
				canAdvance = false;
			}
			break;
	}
}