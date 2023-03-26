#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../General Components/HealthComponent.h"
#include "../../gameObjects/Player Object/Player.h"

// Clase abstracta que junta la logica común del comportamiento enemigo como su posición,
// la del jugador y su velocidad

class EnemyBehaviour: public Component
{
protected:
	Transform* pos;
	Transform* playerPos;
	HealthComponent* life;
	HealthComponent* playerLife;
	Player* player;
	float stopTime;
	double elapsedTime;
	double behaviorTime;
	float attackInterval;
	float speed;
	int damage;
	bool attacking;
	vector<GameObject*>::iterator posVector;
	bool confused;
	// AttackComponent* attack (cuando este cerca del player, envia un mensaje para atacar)

public:
	static const int id = _ENEMY_BEHAVIOUR;

	//Constructora para la herencia
	EnemyBehaviour(float spd, int dmg, float stop, float attack, Player* plyr) : 
		speed(spd), damage(dmg), stopTime(stop), attackInterval(attack), attacking(false), elapsedTime(0), behaviorTime(SDL_GetTicks()),
		player(plyr), pos(nullptr), playerPos(plyr->getComponent<Transform>()),
		life(nullptr), playerLife(plyr->getComponent<HealthComponent>()), 
		confused(false) {
	};

	virtual void initComponent(){
		pos = gObj->getComponent<Transform>();
		assert(pos != nullptr);
	}


	//Setea la posicion en el vector de enemigos
	void setEnemyPosition(vector<GameObject*>::iterator _it) { posVector = _it; }
	// Devuelve si el enemigo est� en acci�n de ataque
	inline bool isAttacking() { return attacking; }
	void setConfusion(bool cnf) {confused = cnf;}
	bool isConfused() { return confused; }
};

