#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include "../General Components/HeatlhComponent.h"
#include <vector>

// Este componente maneja el comportamiento de los objetos Slash creados, 
class SwordSlashBehaviour : public Component {

private:
	int damage;
	vector<bool> hitRegistry;
	int actualObject;
public:
	static const int id = _SWORD_BEHAVIOUR;
	// Recibe un vector de enemigos con los que debera colisionar la bala del player y crea el vector de colisionados del mismo tamaño
	SwordSlashBehaviour(int dmg, grpId Target);

	CallBackCol swordAttack();
};