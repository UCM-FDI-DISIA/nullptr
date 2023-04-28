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

public:
	// Constructora
	TutorialScene(BattleType bt);

	// Notifica de que se ha descartado una carta
	void notifyDiscard();

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

	// Devuelve los callbacks con sus respectivos tiempos
	vector<pair<CallBack, double>> getSteps();
};