#include "SwordSlashBehaviour.h"
#include "../../scenes/GameState.h"
SwordSlashBehaviour:: SwordSlashBehaviour(int dmg, grpId Target)
{
	hitRegistry.assign(gStt->getEntitiesByGroup(Target).size(), false);
	damage = dmg;
	actualObject = 0;
}

CallBackCol SwordSlashBehaviour::swordAttack()
{
	return [&](GameObject* trgt) {
		//Comprueba si ya ha colisionado anteriormente con el mismo objeto
		if (!hitRegistry[actualObject]) {
			cout << "hizo damages" << endl;
			//Hace el daño y lo añade a la lista de ya colisionados
			trgt->getComponent<HealthComponent>()->receiveDamage(damage);
			hitRegistry[actualObject] = true;
		}
		actualObject++;
		if (actualObject >= hitRegistry.size())actualObject = 0; // Evita atacar a objetos ya colisionados
	};
}