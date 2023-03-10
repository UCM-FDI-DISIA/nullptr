#pragma once
#include "Component.h"
#include "Transform.h"
#include "ColliderComponent.h"
#include "HeatlhComponent.h"
#include "../gameObjects/Player.h"

// Clase abstracta que junta la logica com?n del comportamiento enemigo como su posici?n,
// la del jugador y su velocidad

class EnemyBehavior: public Component
{
protected:
	Transform* pos;
	Transform* playerPos;
	HealthComponent* life;
	HealthComponent* playerLife;
	Player* player;
	float stopTime;
	float elapsedTime;
	float actualTime;
	float attackInterval;
	float speed;
	int damage;
	vector<GameObject*>::iterator posVector;
	// AttackComponent* attack (cuando este cerca del player, envia un mensaje para atacar)
public:
	
	//Constructora para la herencia
	EnemyBehavior(float spd, int dmg, float stop, float attack, Player* plyr) : speed(spd), damage(dmg), stopTime(stop), attackInterval(attack) {
		player = plyr;
		playerPos = player->getComponent<Transform>();
		actualTime = SDL_GetTicks();
    };

	/*Funciones para borrar enemigos*/

	//Setea la posicion en el vector de enemigos
	void setEnemyPosition(vector<GameObject*>::iterator _it) { posVector = _it; }

	//Devuelve la posicion del enemigo en el vector
	vector<GameObject*>::iterator getEnemyPos() { return posVector; }
};

