#pragma once
#include "EnemyBehaviour.h"
#include "../../core/SDLApplication.h"

class TankBehaviour : public EnemyBehaviour {
private: 
	Transform* transform;
	bool attacking, chargingAttack, attacked;
	float stop, attackingTime;
public:
	static const int id = _TANK_BEHAVIOUR;

	// Constructora
	TankBehaviour(float spd, int dmg, float stop, float attack, Player* plyr);
	// Inicializa el componente
	virtual void initComponent();

	virtual void update();
	
	void setDirectionTo();

	void enemyAttack();
};