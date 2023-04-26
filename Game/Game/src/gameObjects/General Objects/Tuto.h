#pragma once
#include "../GameObject.h"
#include "../../components/General Components/Animator.h"
#include "../../components/General Components/LerpComponent.h"

class Tuto : public GameObject {
private:
	Animator* myAnim;
	LerpComponent* l;
	// Puntero a mi componente de tuto

public:
	// Constructora
	Tuto() : myAnim(nullptr), l(nullptr) { }
	// Inicializa el objeto
	virtual void initGameObject(Transform* pl);

	void createAnims(Animator* a);
	// SE MUEVE CON WASD
	void showMovementControls();
	//
	void showCardsUses();
	void showDiscardCard();
	void showAbility();
	void showSelectCard();
	void showPortalCharges();

};