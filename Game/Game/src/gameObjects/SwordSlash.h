#pragma once
#include "../core/GameObject.h"
#include "../components/ColliderComponent.h"
#include "../components/LifetimeComponent.h"
#include "../components/SwordSlashBehaviour.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../core/SDLApplication.h"

/*
	SWORDSLASH

	Imagen de ataque en arco
	Cuando colisiona POR PRIMERA VEZ con un enemigo, el enemigo recibe damages
	Desaparece a los x segundos

*/

class SwordSlash : public GameObject {
public:

	virtual void initGameObject(Vector2D playerPos, Vector2D dir, BattleScene* scene, int dmg) {
		Vector2D slashVector = playerPos + dir * 100;
		addComponent<Transform>(slashVector, Vector2D(0, 0), 100, 100, slashVector.angle(playerPos));
		addComponent<LifeTimeComponent>(60);
		addComponent<Image>(SDLApplication::getTexture("SwordSlash"));
		addComponent<ColliderComponent>();
		addComponent<SwordSlashBehaviour>(dmg, scene->getEnemies());
	}
};