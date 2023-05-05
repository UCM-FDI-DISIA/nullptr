#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../../components/Card Components/CardComponent.h"
#include "Hitbox.h"

//Se crea una bala en la posici�n del jugador y se dirige hacia el cursor
void BowCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
	//Comprobaci�n de que la cadencia no ha sido modificada previamente
	if (downtime != BOW_CADENCE) downtime = BOW_CADENCE;

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();
	float rot = where->getPointer()->getComponent<Transform>()->getRotation() - 90;

	for (int i = 0; i < 3; i++) {
		Hitbox::HitboxData data = { playerPos, dir.rotate(-10 + i*10) * ARROW_SPEED, rot - 10 + i*10, 50, 10, PLAYER_ARROW, _grp_ENEMIES};

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, 10, data);
	}
}

//Se disparan todas las flechas
void BowCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
		dir = dir.normalize();
		float rot = where->getPointer()->getComponent<Transform>()->getRotation() - 90;

		Hitbox::HitboxData data = { playerPos, dir * ARROW_SPEED, rot, 16, 16, PLAYER_ARROW, _grp_ENEMIES };

		float size = 100 + remainingUses * 30;
		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 2 * damage * attackMult, false, 0.75, StatusComponent::NONE, size, size, "BowSkill", 280, 280, 2, 2, Animation(0, 3, 10, 1), where, data);
	remainingUses = 0;

}