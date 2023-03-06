#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../../components/Card Components/CardComponent.h"
#include "../Card Objects/Bullet.h"

//Se crea una bala en la posición del jugador y se dirige hacia el cursor
void SMGCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	where->addGameObject<Bullet>(playerPos, dir, damage * attackMult, where->getEnemies());
}

//Se disparan todas las balas
void SMGCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	downtime /= 2;
	CardComponent* component = where->getPlayer()->getComponent<CardComponent>();
	component->lock();
	component->setAutomatic();
}
