#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"



class SwordSpin : public GameObject {
public:
/*
	Imagen de ataque circular en el centro del jugador
	Cuando colisiona POR PRIMERA VEZ con un enemigo, el enemigo recibe daño
	Desaparece a los 60 milisegundos
*/
	virtual void initGameObject(Vector2D playerPos, BattleScene* scene, int dmg) {
<<<<<<< Updated upstream
		addComponent<Transform>(playerPos - Vector2D(100, 100), Vector2D(0, 0), 200, 200);
		addComponent<LifeTimeComponent>(.1);
=======
		addComponent<Transform>(playerPos - Vector2D(WIDTH /2, HEIGHT /2), Vector2D(0, 0), WIDTH, HEIGHT);
		addComponent<LifeTimeComponent>(1);
>>>>>>> Stashed changes
		addComponent<Image>(SDLApplication::getTexture("SwordSpin"));
		addComponent<SwordSlashBehaviour>(dmg, scene->getEnemies());
		addComponent<ColliderComponent>();
	}

private:
	const float HEIGHT = 200;
	const float WIDTH = 200;
};