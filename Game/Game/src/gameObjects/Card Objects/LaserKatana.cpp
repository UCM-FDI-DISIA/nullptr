#include "Cards.h"
#include "../Card Objects/Hitbox.h"

void LaserKatanaCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos, VECTOR_ZERO, rotation, 250, 70, "null", _grp_ENEMIES };
	data.pos = data.pos + Vector2D(data.width / 2, 0);

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, DASH_DURATION, data, Vector2D(0, data.height / 2));
	where->getPlayer()->getComponent<PlayerMovementComponent>()->dash(dir);
	where->getPlayer()->getComponent<HealthComponent>()->setInvencibility(DASH_DURATION*3);

	auto slashAnim = where->addGameObject<GameObject>();

	auto spritePosition = playerPos + dir * 100 - Vector2D(PLAYER_SPRITE_WIDTH * 2, PLAYER_SPRITE_HEIGHT * 3);
	slashAnim->addComponent<Transform>(spritePosition, VECTOR_ZERO, 100, 200, rotation);
	auto anim = slashAnim->addComponent<Animator>(SDLApplication::getTexture("NeonSlash"), 96, 192, 1, 9);
	anim->createAnim("NeonSlash", Animation(0, 8, 20, 1));
	anim->play("NeonSlash");
	slashAnim->addComponent<LifeTimeComponent>(0.4);

}

void LaserKatanaCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	dir = dir.normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	for (int i = 0; i < remainingUses; i++) {
		
		Vector2D aux = dir * LASER_KATANA_BURST * (i - 1);
		Hitbox::HitboxData data = { playerPos + aux, dir * BULLET_SPEED, rotation, 15, 150, LASER, _grp_ENEMIES};

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 10, data);
	}

	remainingUses = 0;
}
