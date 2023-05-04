#pragma once
#include "../Component.h"
#include "../../gameObjects/Card Objects/Hitbox.h"

class HitboxExplosionComponent :  public Component
{
private:
    //Duracion del gObj
	int damage;
    float lifeSpan;
	StatusComponent::status stts;
    float currentLifeDuration;
	bool contact; //Si explota al contacto
	float  width;//tamaño explosion
	float height;//tamaño explosion
	string sprite;//sprite area explosion
    BattleScene* scene;
    grpId target;
	Transform* tr;
	CallBackExpl cb;

	bool animated = false;
	AnimatorInfo animatorInfo;
	Animation animation;

public:
    //Constructora. Determina el tick global en el que el gObj muere, la escena en la que se instancia la explosion y el daño que hace esta
    HitboxExplosionComponent(int dmg, float lifeSpan, StatusComponent::status stts, bool cntct, float  wdth, float hght,string sprt,  BattleScene* scn, grpId trgt, CallBackExpl funct = nullptr) 
		: damage(dmg), lifeSpan(lifeSpan), currentLifeDuration(0), width(wdth), height(hght), sprite(sprt), scene(scn), target(trgt), tr(nullptr), contact(cntct), cb(funct) {}

	HitboxExplosionComponent(int dmg, float lifeSpan, StatusComponent::status stts, bool cntct, float  wdth, float hght, string sprt, BattleScene* scn, grpId trgt, AnimatorInfo animatorInfo, Animation animation, CallBackExpl funct = nullptr)
		: damage(dmg), lifeSpan(lifeSpan), currentLifeDuration(0), width(wdth), height(hght), sprite(sprt), scene(scn), target(trgt), tr(nullptr), contact(cntct), cb(funct), animated(true), animatorInfo(animatorInfo), animation(animation) {}
    static const int id = _HITBOX_EXPLOSION_COMPONENT;

	// Se le añade al colider la funcion de explosion
	void initComponent()
	{
		tr = gObj->getComponent<Transform>();
		if (contact) { 
			gObj->getComponent<ColliderComponent>()->addFunction(explosionFunction()); 
			if (cb != nullptr) gObj->getComponent<ColliderComponent>()->addFunction(cb);
		}
	}


	//Checkea que haya pasado el tiempo establecido y elimina el gObj creando una explosion en caso positivo
	void update()
	{
		currentLifeDuration += SDLApplication::instance()->getDeltaTimeSeconds();
		if (currentLifeDuration > lifeSpan)
		{

			Hitbox::HitboxData data = { tr->getCenter(), VECTOR_ZERO, 0, width, height, sprite, target };

			// Ejecuto mi funcion
			if (cb != nullptr) cb(tr);
			auto hb = scene->addGameObject<Hitbox>(gObj->getGroup(), damage, false, 4, stts, 0.25, data);
			if (animated)
			{
				auto a = hb->addComponent<Animator>(SDLApplication::getTexture(animatorInfo.key), animatorInfo.w, animatorInfo.h, animatorInfo.rows, animatorInfo.cols);
				a->createAnim("animation", animation);
				a->play("animation");
			}
			gObj->setAlive(false);
		}
	}

	//Funcion que se llama al colisionar, elimina el gObj creando una explosion
	CallBackCol explosionFunction()
	{
		return [&](GameObject* trgt) {
			Hitbox::HitboxData data = { tr->getCenter(), VECTOR_ZERO, 0, width, height, sprite, target };

			auto hb = scene->addGameObject<Hitbox>(gObj->getGroup(), damage, false, 4, stts, 0.25, data);
			if (animated)
			{
				auto a = hb->addComponent<Animator>(SDLApplication::getTexture(animatorInfo.key), animatorInfo.w, animatorInfo.h, animatorInfo.rows, animatorInfo.cols);
				a->createAnim("animation", animation);
				a->play("animation");
			}


			gObj->setAlive(false);
		};
	}

};