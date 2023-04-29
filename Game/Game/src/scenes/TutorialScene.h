#pragma once
#include "BattleScene.h"
#include "../gameObjects/General Objects/Tuto.h"
#include "../components/General Components/TutorialComponent.h"

class TutorialScene : public BattleScene {
private:
	// Objetos de tutorial
	TutorialComponent* tutorialController;
	Tuto* tuto;
	// Enemigo para testear
	GameObject* testEnemy;
	// Cosas del popup
	GameObject* screen;
	GameObject* tutoPopUp;
	GameObject* text;
	Button* button;
	// Paso en el que estamos
	int current;

	string tutorialTexts[8] = {
		// Movimiento
		"¡Bienvenido a Timeless Deck! Yo soy Tuto y voy a ser tu guía en este lugar.\nPara empezar, siempre que aparezca aquí debes pulsar 'REANUDAR' para continuar.\n\nDicho esto, prueba a moverte con los controles que te voy a mostrar por pantalla.",
		
		// Carta
		"¡Muy bien! Pues ya va siendo hora de enseñarte la magia de este lugar... ¡tus armas son cartas!\n\nMira, voy a darte una para probar, aunque realmente puedes llevar hasta 4 como máximo en tu mano.\nFíjate en mi pantalla para aprender a apuntar y disparar y en la carta para ver sus usos.",
		
		// Mano
		"¡Genial! Además de las 4 cartas de tu mano, contarás con una pila de descartes y un mazo, cada uno a un lado.\nCuando gastes una carta, esta pasará a los descartes y, de ser la última de la mano, cogerás 4 nuevas del mazo. Estos mazos ciclarán entre ellos, y el mazo se barajeará cada vez que se acabe con la pila. ¡Pruébalo!",
		
		// Enemigos
		"¡Aprendes rápido, eh! En este lugar deberás derrotar enemigos para poder avanzar. Estos enemigos te quitarán vida si te golpean, así que dalo todo para derrotarlos.\n\nPor ahora, cuentas con 100 puntos de vida (barra roja), pero cada enemigo te hará un daño diferente. Recuerda que puedes seleccionar qué carta usas.",
		
		// Habilidad
		"¿Has visto eso? ¡El enemigo te ha soltado maná! (piedras azules).\n\nEl maná (barra azul) será necesario para usar las habilidades de las cartas y para recogerlo deberás pasar sobre él.\nLas habilidades vienen indicadas en la zona superior de las cartas junto al maná que consumen, ¡prueba a usar una!",
	
		// Portal
		"El enemigo te puede soltar otra cosa... ¡éter! (polvo morado).\n\nEl éter (barra blanca) será necesario para cargar el portal, teniendo que llegar al 100% del medidor para poder avanzar al siguiente nivel. Se recogerá solo tras cierto tiempo, así que... ¡ánimo contra la siguiente horda de enemigos!"
	};

public:
	// Constructora
	TutorialScene(BattleType bt);

	// Notifica de que se ha descartado una carta, que se crea una nueva mano y que se ha usado una habilidad
	void notifyDiscard() {
		tutorialController->setDiscarted(true);
	}

	void notifyNewHand() {
		tutorialController->setNewHand(true);
	}

	void notifyAbility() {
		tutorialController->setAbility(true);
	}

	// PASOS DEL TUTORIAL
	// Activar input 
	void activateInput();
	// Añadir carta (enseñar como se apunta y como se usan)	
	void addCard();
	// Enseña sobre el sistema de cartas
	void explainCardSystem();
	// Añadir enemigos (matarlos) y las barras de vida y mana
	void addMeleeEnemy();
	// Enseñar a usar las habilidades de las cartas (y que el mana baja)
	void showAbility();
	// Añadir aun mas enemigos y mostrar que sube el maná si droppean
	void showDrops();
	// Explicar que los enemigos cargan el portal
	void showPortalCharges();
	// Activa el popup
	void activatePopUp();
	// Desactiva el popup
	void deactivatePopUp();

	// Comprueba si hay enemigos o mana en la escena
	void showPopUpText(Vector2D tutoPos);
	bool getTestEnemy() { return getEntitiesByGroup(_grp_ENEMIES).size() == 0; };
	bool getManaNumber() { return getEntitiesByGroup(_grp_MANA).size() == 0; }

	// Devuelve los callbacks con sus respectivos tiempos
	vector<CallBack> getSteps();
};