#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/HitboxDamageComponent.h"
#include "../../components/Card Components/HitboxStatusComponent.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"

class RitualAxeCard;

class Hitbox : public GameObject {
public:

	//Struct con la informaci�n b�sica para instanciar cualquier hitbox
	struct HitboxData
	{
		Vector2D pos, vel; // Posicion inicial y velocidad de movimiento
		float rot, width, height; //  Rotacion, anchura y altura
		string texture; // String de la textura correspondiente
		grpId trgt; // Grupo con el que debe colisionar dicha hitbox
	};

	//Constructor basico de hitbox sin funcionalidad, recibe un HitboxData y un anchor point que por defecto se coloca en el centro de esta
	void initGameObject(HitboxData data, Vector2D anch = Vector2D(-1,-1)) {
		if (anch.getX() == -1) anch = Vector2D(data.width / 2, data.height / 2);
		addComponent<Transform>(data.pos - Vector2D(data.width/2, data.height/2), data.vel, anch, data.width, data.height, data.rot);
		addComponent<Image>(SDLApplication::getTexture(data.texture));
		addComponent<ColliderComponent>(data.trgt);
	}

	//Constructor de hitbox que causa dano, se le anade un lifetime component
	void initGameObject(int dmg, bool isDestroyed, bool knockBack, float lifetime, HitboxData data, Vector2D anch = Vector2D(-1, -1), RitualAxeCard* axe = nullptr)
	{
		initGameObject(data, anch);
		addComponent<LifeTimeComponent>(lifetime);
		addComponent<HitboxDamageComponent>(dmg, isDestroyed, knockBack, axe);
	}

	//Constructor de hitbox que aflige estados alterados, se le anade un lifetime component
	void initGameObject(float drtn, StatusComponent::status stts, float lifetime, HitboxData data, Vector2D anch = Vector2D(-1, -1))
	{
		initGameObject(data, anch);
		addComponent<LifeTimeComponent>(lifetime);
		addComponent<HitboxStatusComponent>(stts, drtn);
	}

	//Constructor de hitbox que aflige estatus y causa dano, se le anade un lifetime component
	void initGameObject(int dmg, bool isDestroyed, bool knockBack, float drtn, StatusComponent::status stts, float lifetime, HitboxData data, Vector2D anch = Vector2D(-1, -1))
	{
		initGameObject(dmg, isDestroyed, knockBack, lifetime, data, anch);
		addComponent<HitboxStatusComponent>(stts, drtn);
	}

	//Constructor de hitbox que crea una explosion

	//Constructor de hitbox que crea una area de curación
	void initGameObject(int healing, float cooldown, HitboxData data, float lifetime, Vector2D anch = Vector2D(-1, -1));

	void initGameObject(int dmg, bool contact, float lifetime, StatusComponent::status stts, float width, float height, string sprite, BattleScene* scene, HitboxData data, Vector2D anch = Vector2D(-1, -1));

	// Constructor de hitbox que no causa daño ni inflige estados alterados, se le añade un lifetime component
	void initGameObject(float lifetime, HitboxData data, Vector2D anch = Vector2D(-1, -1)) {
		initGameObject(data, anch);
		addComponent<LifeTimeComponent>(lifetime);
		addComponent<ColliderComponent>(data.trgt); 
	}
	// Agrega este método predeterminado a la clase Hitbox
	void initGameObject() {}


};
