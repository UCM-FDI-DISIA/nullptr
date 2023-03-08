#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/SwordSlashBehaviour.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"



class Hitbox : public GameObject {
public:
	/*
	Imagen de ataque circular en arco en la direcci�n que apunta el jugador
	Cuando colisiona POR PRIMERA VEZ con un enemigo, el enemigo recibe da�o
	Desaparece a los 60 milisegundos
*/
	virtual void initGameObject(Vector2D playerPos, Vector2D dir, BattleScene* scene, int dmg, Texture* texture, grpId trgt) {
		Vector2D slashVector = playerPos + dir * 100;
		addComponent<Transform>(slashVector - Vector2D(texture->width() / 2, texture->height() / 2), Vector2D(0, 0), texture->width(), texture->height(), Vector2D(1, 0).angle(dir));
		addComponent<LifeTimeComponent>(0.06);
		addComponent<Image>(texture);
		addComponent<SwordSlashBehaviour>(dmg, trgt);
		addComponent<ColliderComponent>(getComponent<SwordSlashBehaviour>()->swordAttack(), trgt);
	}
};
