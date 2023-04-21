#include "Cards.h"
#include "../Card Objects/Hitbox.h"

// Crea un gObj Slash en la direcci�n que apunta el jugador
void SwordCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = {playerPos + dir * 100, Vector2D(), rotation, 200, 100, Constant::getString("SWORD_SLASH"), _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.06, data);

}

// Crea un gObj Spin en el centro del jugador
void SwordCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	
	Hitbox::HitboxData data = {playerPos, Vector2D(), 0, 300, 300, Constant::getString("SWORD_SPIN"), _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.1, data);

	remainingUses = 0;
}
