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

public:
    //Constructora. Determina el tick global en el que el gObj muere, la escena en la que se instancia la explosion y el daño que hace esta
    HitboxExplosionComponent(int dmg, float lifeSpan, StatusComponent::status stts, bool cntct, float  wdth, float hght,string sprt,  BattleScene* scn, grpId trgt) : damage(dmg), lifeSpan(lifeSpan), currentLifeDuration(0), width(wdth), height(hght), sprite(sprt), scene(scn), target(trgt), tr(nullptr), contact(cntct) {}
    static const int id = _HITBOX_EXPLOSION_COMPONENT;

	// Se le añade al colider la funcion de explosion
	void initComponent()
	{
		tr = gObj->getComponent<Transform>();
		if(contact) gObj->getComponent<ColliderComponent>()->addFunction(explosionFunction());
	}


	//Checkea que haya pasado el tiempo establecido y elimina el gObj creando una explosion en caso positivo
	void update()
	{
		currentLifeDuration += SDLApplication::instance()->getDeltaTimeSeconds();
		if (currentLifeDuration > lifeSpan)
		{

			Hitbox::HitboxData data = { tr->getCenter(), VECTOR_ZERO, 0, width, height, sprite, _grp_ENEMIES };

			scene->addGameObject<Hitbox>(gObj->getGroup(), damage, false, 4, stts, 0.25, data);

			gObj->setAlive(false);
		}
	}

	//Funcion que se llama al colisionar, elimina el gObj creando una explosion
	CallBackCol explosionFunction()
	{
		return [&](GameObject* trgt) {
			Hitbox::HitboxData data = { tr->getCenter(), VECTOR_ZERO, 0, width, height, sprite, _grp_ENEMIES };

			scene->addGameObject<Hitbox>(gObj->getGroup(), damage, false, 4, stts, 0.25, data);

			gObj->setAlive(false);
		};
	}

};