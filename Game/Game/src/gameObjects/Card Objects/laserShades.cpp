#include "Cards.h"
#include "../Card Objects/Hitbox.h"
#include "../../sdlutils/Texture.h"

void LaserShadesCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
    Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
    Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
    float rotation = Vector2D(1, 0).angle(dir);

    float parallelDistance = 20.0f; // Distancia entre los rayos paralelos

    // Primer rayo paralelo
    Vector2D offset1 = Vector2D(0, -parallelDistance / 2).rotate(rotation);
    Hitbox::HitboxData data1 = { playerPos + offset1, dir * LASER_BULLET_SPEED, rotation, 100, 10, LASER, _grp_ENEMIES };
    data1.pos = data1.pos + Vector2D(data1.width / 2, 0);
    where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 3, data1, Vector2D(0, data1.height / 2));

    // Segundo rayo paralelo
    Vector2D offset2 = Vector2D(0, parallelDistance / 2).rotate(rotation);
    Hitbox::HitboxData data2 = { playerPos + offset2, dir * LASER_BULLET_SPEED, rotation, 100, 10, LASER, _grp_ENEMIES };
    data2.pos = data2.pos + Vector2D(data2.width / 2, 0);
    where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 3, data2, Vector2D(0, data2.height / 2));
}


void LaserShadesCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
	float rot = Vector2D(1, 0).angle(mousePos - playerPos - where->getCamera()->getOffset());
	float parallelDistance = 20.0f; // Distancia entre los rayos paralelos

	for (int i = 0; i < 2 * remainingUses; i++)
	{
		float rotation = rot + (i * 360 / remainingUses);
		Vector2D dir = Vector2D(1, 0).rotate(rotation);

		// Primer rayo paralelo
		Vector2D offset1 = Vector2D(0, -parallelDistance / 2).rotate(rotation);
		Hitbox::HitboxData data1 = { playerPos + offset1, dir * LASER_BULLET_SPEED, rotation, 100, 10, LASER, _grp_ENEMIES };
		data1.pos = data1.pos + Vector2D(data1.width / 2, 0);
		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 3, data1, Vector2D(0, data1.height / 2));

		// Segundo rayo paralelo
		Vector2D offset2 = Vector2D(0, parallelDistance / 2).rotate(rotation);
		Hitbox::HitboxData data2 = { playerPos + offset2, dir * LASER_BULLET_SPEED, rotation, 100, 10, LASER, _grp_ENEMIES };
		data2.pos = data2.pos + Vector2D(data2.width / 2, 0);
		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 3, data2, Vector2D(0, data2.height / 2));
	}

	remainingUses = 0;
}

