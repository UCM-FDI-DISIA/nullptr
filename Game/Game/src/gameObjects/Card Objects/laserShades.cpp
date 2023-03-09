#include "Cards.h"
#include "../Card Objects/Hitbox.h"
#include "../../sdlutils/Texture.h"

void LaserShadesCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir*5, VECTOR_ZERO, rotation, 1100, 10, "Laser", _grp_ENEMIES };
	data.pos = data.pos + Vector2D(data.width / 2, 0);

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.08, data, Vector2D(0, data.height/2));
}

void LaserShadesCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rot = Vector2D(1, 0).angle(dir);


	for (int i = 0; i < 2 * remainingUses; i++)
	{
		float rotation = rot + (i * 360 / remainingUses);

		Hitbox::HitboxData data = { playerPos + Vector2D(5,0).rotate(rotation), VECTOR_ZERO, rotation, 1100, 10, "Laser", _grp_ENEMIES};
		data.pos = data.pos + Vector2D(data.width / 2, 0);

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.08, data, Vector2D(0, data.height / 2));
	}
	remainingUses = 0;
}
