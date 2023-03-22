#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"



class HelaingCloud : public GameObject {
public:
	/*
		Imagen de ataque circular en el centro del jugador
		Cuando colisiona con el player, se cura la vida
		Desaparece a los 2 segundos
	*/
	virtual void initGameObject(Vector2D playerPos, BattleScene* scene, int dmg) {
		addComponent<Transform>(playerPos - Vector2D(WIDTH / 2, HEIGHT / 2), Vector2D(0, 0), WIDTH, HEIGHT);
		addComponent<LifeTimeComponent>(1);
		addComponent<Image>(SDLApplication::getTexture("SwordSpin"));
		//addComponent<SwordSlashBehaviour>(dmg, scene->getEnemies());
		addComponent<ColliderComponent>();
	}

private:
	const float HEIGHT = 200;
	const float WIDTH = 200;
};