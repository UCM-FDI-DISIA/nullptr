#pragma once
#include "../GameObject.h"
#include "../../components/General Components/Animator.h"
#include "../../components/General Components/LerpComponent.h"

class Tuto : public GameObject {
private:
	Animator* myAnim;
	LerpComponent* l;
	Transform* tr;
	int current;
	double time;
	bool change;

public:
	// Constructora
	Tuto() : myAnim(nullptr), l(nullptr), time(0) { }
	// Inicializa el objeto
	virtual void initGameObject(Transform* pl);
	virtual void update();

	//void createAnims(Animator* a);
	//// SE MUEVE CON WASD
	//void showMovementControls();
	////
	//void showCardsUses();
	//void showDiscardCard();
	//void showAbility();
	//void showSelectCard();
	//void showPortalCharges();

	void changeAnim(int current);
};