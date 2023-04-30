#pragma once
#include "EnemyBehaviour.h"
#include "../../core/SDLApplication.h"


class TankBehaviour : public EnemyBehaviour{
private: 
	Transform* transform;
	bool startAttack, chargingAttack, attacked;
	float attackingTime;
public:
	static const int id = _ENEMY_BEHAVIOUR;

	// Constructora
	TankBehaviour(float spd, int dmg, float stop, float attack, Player* plyr);
	// Inicializa el componente
	virtual void initComponent();

	virtual void update();
	
	void setDirectionTo();

	void enemyAttack();

	CallBackCol tankAttack();
};