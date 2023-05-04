#pragma once
#include "Hitbox.h"
#include "../../components/Card Components/HitboxExplosionComponent.h"
#include "../../components/Card Components/HitboxHealingComponent.h"

//Constructor de hitbox que crea una explosion
void Hitbox::initGameObject(int dmg, bool contact, float lifetime, StatusComponent::status stts, float width, float height,string sprite, BattleScene* scene, HitboxData data, Vector2D anch, CallBackExpl cb)
{
	initGameObject(data, anch);
	addComponent<HitboxExplosionComponent>(dmg, lifetime, stts, contact, width, height, sprite, scene, data.trgt, cb);
}

void Hitbox::initGameObject(int dmg, bool contact, float lifetime, StatusComponent::status stts, float width, float height,string sprite, int spriteWidth, int spriteHeight, int rows, int columns, Animation anim, BattleScene* scene, HitboxData data, Vector2D anch, CallBackExpl cb)
{
	if (anch.getX() == -1) anch = Vector2D(data.width / 2, data.height / 2);
	addComponent<Transform>(data.pos - Vector2D(data.width / 2, data.height / 2), data.vel, anch, data.width, data.height, data.rot);
	auto animator = addComponent<Animator>(SDLApplication::getTexture(sprite), spriteWidth, spriteHeight, rows, columns);
	animator->createAnim("xplosion", anim);
	animator->play("xplosion");
	addComponent<ColliderComponent>(data.trgt);
	addComponent<HitboxExplosionComponent>(dmg, lifetime, stts, contact, width, height, sprite, scene, data.trgt, cb);
}

void Hitbox::initGameObject(int healing, float cooldown, HitboxData data, float lifetime, Vector2D anch)
{
	initGameObject(data, anch);
	addComponent<LifeTimeComponent>(lifetime);
	addComponent<HitboxHealingComponent>(healing, cooldown);
}
