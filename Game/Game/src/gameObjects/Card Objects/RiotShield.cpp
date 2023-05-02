#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"
#include <iostream>
#include "CustomHitbox.h"

// Crea un gObj Slash en la dirección que apunta el jugador
void RiotShieldCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, VECTOR_ZERO, rotation, 100, 120, "null", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 0.06, data, Vector2D(-1, -1), nullptr, playerPos);

    auto slashAnim = where->addGameObject<GameObject>();

    auto spritePosition = playerPos + dir * 100 - Vector2D(PLAYER_SPRITE_WIDTH * 2, PLAYER_SPRITE_HEIGHT * 3);
    slashAnim->addComponent<Transform>(spritePosition, VECTOR_ZERO, 100, 200, rotation);
    auto anim = slashAnim->addComponent<Animator>(SDLApplication::getTexture("ShieldSlash"), 96, 192, 1, 9);
    anim->createAnim("ShieldSlash", Animation(0, 8, 20, 1));
    anim->play("ShieldSlash");
    slashAnim->addComponent<LifeTimeComponent>(0.4);


}


// Crea un gObj para proteger al jugador
void RiotShieldCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 50, dir * SHIELD_SPEED, rotation, 200, 100, SWORD_SLASH, _grp_ENM_ATTACK };

    auto shield = where->addGameObject<CustomHitbox>();
    shield->initCustomHitbox(data);
    shield->addComponent<LifeTimeComponent>(remainingUses*1.0f);

	auto shieldTransform = shield->getComponent<Transform>();
	auto playerTransform = where->getPlayer()->getComponent<Transform>();

	auto shieldCollider = shield->getComponent<ColliderComponent>();

	shield->setUpdateFunction([=](GameObject* shield) {
		checkCollisionWithBullets(shield, where);
		});

	remainingUses = 0;
}
void RiotShieldCard::checkCollisionWithBullets(GameObject* shield, BattleScene* where) {
    // Obtén todos los objetos del grupo _grp_ENM_ATTACK
    auto bullets = where->getEntitiesByGroup(_grp_ENM_ATTACK);

    // Recorre todos los objetos del grupo
    for (auto& bullet : bullets) {
        Transform* shieldTransform = shield->getComponent<Transform>();
        Vector2D& shieldPos = shieldTransform->getPos();
        float shieldWidth = shieldTransform->getWidth();
        float shieldHeight = shieldTransform->getHeight();
        float shieldRot = shieldTransform->getRotation();
        Vector2D shieldAnch = shieldTransform->getAnchorPoint();

        Transform* bulletTransform = bullet->getComponent<Transform>();
        Vector2D& bulletPos = bulletTransform->getPos();
        float bulletWidth = bulletTransform->getWidth();
        float bulletHeight = bulletTransform->getHeight();
        float bulletRot = bulletTransform->getRotation();
        Vector2D bulletAnch = bulletTransform->getAnchorPoint();

        // Comprueba si la bala y el escudo están colisionando
        if (Collisions::collidesWithRotation(shieldPos, shieldWidth, shieldHeight, shieldRot, shieldAnch,
            bulletPos, bulletWidth, bulletHeight, bulletRot, bulletAnch)) {
            // Destruye la bala
            bullet->setAlive(false);
        }
    }
}


