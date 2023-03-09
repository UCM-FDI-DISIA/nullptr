#pragma once
#include "Hitbox.h"
#include "../../components/Card Components/HitboxExplosionComponent.h"

void Hitbox::initGameObject(int dmg, bool contact, float lifetime, BattleScene* scene, HitboxData data, Vector2D anch)
{
	initGameObject(data, anch);
	addComponent<HitboxExplosionComponent>(dmg, lifetime, contact, scene, data.trgt);
}
