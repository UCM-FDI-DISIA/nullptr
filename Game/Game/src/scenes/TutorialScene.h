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
		"Bienvenido a Timeless Deck. Soy Tuto y seré tu guía.\nPara empezar, siempre que aparezca aquí debes pulsar 'REANUDAR' para continuar.\n\nDicho esto, prueba a moverte con los controles que te mostraré por pantalla.",
		
		// Carta
		"¡Muy bien! Pues ya va siendo hora de enseñarte la magia de este lugar... ¡tus armas son cartas!\n\nMira, voy a darte una para probar, aunque realmente puedes llevar hasta 4 como máximo en tu mano.",
		
		// Mano
		"¡Genial! Además de tu mano, tienes un mazo y una pila de descartes. Las cartas gastadas van a los descartes y se toman 4 nuevas del mazo si se acaba la mano. Al agotarse el mazo, se ciclan los descartes.",
		
		// Enemigos
		"¡Aprendes rápido, eh!\nDebes vencer enemigos para avanzar, pero te quitarán vida si te golpean. Tienes 100 puntos de vida (barra roja) y cada enemigo hace un daño diferente. Escoge tus cartas sabiamente.",
		
		// Habilidad
		"¿Has visto eso? \nRecoge el maná que sueltan los enemigos para usar habilidades indicadas en las cartas junto al maná que consumen.",
	
		// Portal
		"Los enemigos también pueden soltar éter (polvo morado) que necesitas para cargar el portal y avanzar al siguiente nivel. Recógelo y derrota enemigos para llenar el medidor al 100%.",
	
		// Fin
		"¡Bien hecho, eso es todo! Ahora llenaré tu barra de éter al 100% y podrás salir del nivel tal y como te voy a indicar por pantalla.\n\nCon esto dicho, solo me queda despedirme. ¡Ánimo en tu aventura, nos vemos!"
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

	void hideTuto();

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