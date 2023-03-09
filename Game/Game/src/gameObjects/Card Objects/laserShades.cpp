#include "Cards.h"
#include "../Card Objects/Hitbox.h"
#include "../../sdlutils/Texture.h"

void LaserShadesCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 10, VECTOR_ZERO, Vector2D(data.width / 2, data.height / 2), 10, 1100, rotation, "Laser", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.08, data);
}

void LaserShadesCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rot = Vector2D(1, 0).angle(dir);


	for (int i = 0; i < 2 * remainingUses; i++)
	{
		float rotation = rot + (i * 360 / remainingUses);

		Hitbox::HitboxData data = { playerPos + Vector2D(10,0).rotate(rotation), VECTOR_ZERO, Vector2D(data.width / 2, data.height / 2), 10, 1100, rotation, "Laser", _grp_ENEMIES};

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.08, data);
	}
	remainingUses = 0;
}
