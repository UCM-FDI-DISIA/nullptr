#include "Cards.h"
#include "../Card Objects/Hitbox.h"
#include "../../sdlutils/Texture.h"

void LaserShadesCard::spawnRay(Vector2D playerPos, Vector2D dir, float rotation, float attackMult, BattleScene* where, float speed, Vector2D offset) {
    Hitbox::HitboxData data = { playerPos + offset, dir * speed, rotation, 100, 10, LASER, _grp_ENEMIES };
    data.pos = data.pos + Vector2D(data.width / 2, 0);
    where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 3, data, Vector2D(0, data.height / 2));
}

void LaserShadesCard::spawnParallelRays(Vector2D playerPos, Vector2D dir, float rotation, float attackMult, BattleScene* where, float speed) {
    float parallelDistance = 20.0f; // Distancia entre los rayos paralelos
    spawnRay(playerPos, dir, rotation, attackMult, where, speed, Vector2D(0, -parallelDistance / 2).rotate(rotation));
    spawnRay(playerPos, dir, rotation, attackMult, where, speed, Vector2D(0, parallelDistance / 2).rotate(rotation));
}

void LaserShadesCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
    Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
    Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
    float rotation = Vector2D(1, 0).angle(dir);
    spawnParallelRays(playerPos, dir, rotation, attackMult, where, LASER_BULLET_SPEED);
}

void LaserShadesCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
    Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
    Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
    float rot = Vector2D(1, 0).angle(dir);

    for (int i = 0; i < 2 * remainingUses; i++) {
        float rotation = rot + (i * 360 / remainingUses);
        spawnParallelRays(playerPos, dir, rotation, attackMult, where, LASER_BULLET_SPEED_A);
    }

    remainingUses = 0;
}
