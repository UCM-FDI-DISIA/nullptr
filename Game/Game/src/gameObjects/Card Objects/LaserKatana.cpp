#include "Cards.h"
#include "../Card Objects/Hitbox.h"

void LaserKatanaCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos, VECTOR_ZERO, rotation, 250, 70, "null", _grp_ENEMIES };
	data.pos = data.pos + Vector2D(data.width / 2, 0);

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, DASH_DURATION, data, Vector2D(0, data.height / 2));
	where->getPlayer()->getComponent<PlayerMovementComponent>()->dash(dir);
	where->getPlayer()->getComponent<HealthComponent>()->setInvencibility(DASH_DURATION*3);

	auto slashAnim = where->addGameObject<GameObject>();

	auto spritePosition = playerPos - Vector2D(250, 70) / 2;
	slashAnim->addComponent<Transform>(spritePosition, VECTOR_ZERO, 250, 70, rotation);
	auto anim = slashAnim->addComponent<Animator>(SDLApplication::getTexture("NeonDash"), 250, 70, 1, 11);
	anim->createAnim("NeonSlash", Animation(0, 10, 20, 1));
	anim->play("NeonSlash");
	slashAnim->addComponent<LifeTimeComponent>(0.55);

}

void LaserKatanaCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	dir = dir.normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	for (int i = 0; i < remainingUses; i++) {
		
		Vector2D aux = dir * LASER_KATANA_BURST * (i - 1);
		Hitbox::HitboxData data = { playerPos + aux, dir * BULLET_SPEED, rotation, 15, 150, "NeonLaser", _grp_ENEMIES };

		auto hbox = where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, (damage / maxUses) * attackMult, false, 10, data);
		auto anim = hbox->addComponent<Animator>(SDLApplication::getTexture("NeonLaser"), 15, 150, 1, 4);
		anim->createAnim("Laser", Animation(0, 3, 10, -1));
		anim->play("Laser");

	}

	remainingUses = 0;
}
