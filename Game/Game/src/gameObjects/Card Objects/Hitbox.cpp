#pragma once
#include "Hitbox.h"
#include "../../components/Card Components/HitboxExplosionComponent.h"

//Constructor de hitbox que crea una explosion
void Hitbox::initGameObject(int dmg, bool contact, float lifetime, HitboxStatusComponent::Status stts, float width, float height,string sprite, BattleScene* scene, HitboxData data, Vector2D anch)
{
	initGameObject(data, anch);
	addComponent<HitboxExplosionComponent>(dmg, lifetime, stts, contact, width, height, sprite, scene, data.trgt);
}
