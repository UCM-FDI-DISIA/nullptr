#pragma once
#include "BattleScene.h"
#include "../gameObjects/General Objects/Tuto.h"

class TutorialScene : public BattleScene {
private:
	enum Pasos {
		Movimiento, Carta, Descarte, Enemigos, Habilidad, Drops, Portal
	};

	GameObject* screen;
	GameObject* popup;
	Tuto* tuto;
	Pasos current;
	// Generador de enemigos
	GameObject* testEnemy;

public:
	// Constructora
	TutorialScene(BattleType bt);

	// PASOS DEL TUTORIAL
	// Activar input 
	//void activateInput();
	//// Añadir carta (enseñar como se apunta y como se usan)	
	//void addCard();
	//// Añadir enemigos (matarlos) y las barras de vida y mana
	//void addEnemy();
	//// Enseñar a usar las habilidades de las cartas (y que el mana baja)
	//void showAbility();
	//// Añadir aun mas enemigos y mostrar que sube el maná si droppean
	//void showDrops();
	//// Explicar que los enemigos cargan el portal
	//void showPortalCharges();

	void activatePopUp();
	void deactivatePopUp();
};