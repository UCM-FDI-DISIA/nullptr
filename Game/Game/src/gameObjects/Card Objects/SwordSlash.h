#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/SwordSlashBehaviour.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"



class SwordSlash : public GameObject {
public:
	/*
	Imagen de ataque circular en arco en la dirección que apunta el jugador
	Cuando colisiona POR PRIMERA VEZ con un enemigo, el enemigo recibe daño
	Desaparece a los 60 milisegundos
*/
	virtual void initGameObject(Vector2D playerPos, Vector2D dir, BattleScene* scene, int dmg) {
		Vector2D slashVector = playerPos + dir * 100;
		addComponent<Transform>(slashVector, Vector2D(0, 0), 100, 100, slashVector.angle(playerPos));
		addComponent<LifeTimeComponent>(1);
		addComponent<Image>(SDLApplication::getTexture("SwordSlash"));
		addComponent<SwordSlashBehaviour>(dmg, _grp_ENEMIES);
		addComponent<ColliderComponent>(getComponent<SwordSlashBehaviour>()->swordAttack(),_grp_ENEMIES);
	}
};