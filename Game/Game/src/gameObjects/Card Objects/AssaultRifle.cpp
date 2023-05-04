#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"

//Se crea una bala en la posición del jugador y se dirige hacia el cursor
void  AssaultRifleCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	for (int i = 0; i < 4 ; i++) {
		Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

		dir = dir.normalize();
		float rot = where->getPointer()->getComponent<Transform>()->getRotation() - 90;

		playerPos = playerPos + dir * ASSAULT_RIFLE_BURST;

		Hitbox::HitboxData data = { playerPos, dir * GUN_BULLET_SPEED, rot, 20, 10, BULLET, _grp_ENEMIES };

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, 10, data);
	}
}

void  AssaultRifleCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	dir = dir.normalize();
	float rot = where->getPointer()->getComponent<Transform>()->getRotation() - 90;

	Hitbox::HitboxData data = { playerPos, dir * BULLET_SPEED/1.5, rot, 15, 20, GRENADE, _grp_ENEMIES };
	float size = 250;

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 50 * (remainingUses / 8), false, 1, StatusComponent::NONE, size, size, GRENADE_EXPLOSION, where, data);


	remainingUses = 0;

}