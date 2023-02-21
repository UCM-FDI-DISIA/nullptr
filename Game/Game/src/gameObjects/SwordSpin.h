#pragma once
#include "../core/GameObject.h"
#include "../components/ColliderComponent.h"
#include "../components/LifetimeComponent.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../core/SDLApplication.h"



class SwordSpin : public GameObject {
public:
/*
	Imagen de ataque circular en el centro del jugador
	Cuando colisiona POR PRIMERA VEZ con un enemigo, el enemigo recibe daño
	Desaparece a los 60 milisegundos
*/
	virtual void initGameObject(Vector2D playerPos, BattleScene* scene, int dmg) {
		addComponent<Transform>(playerPos - Vector2D(100, 100), Vector2D(0, 0), 200, 200);
		addComponent<LifeTimeComponent>(60);
		addComponent<Image>(SDLApplication::getTexture("SwordSpin"));
		addComponent<SwordSlashBehaviour>(dmg, scene->getEnemies());
		addComponent<ColliderComponent>();
	}
};