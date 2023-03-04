#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../gameObjects/Player Object/Player.h"
#include "../../gameObjects/Enemy Objects/MeleeEnemy.h"
#include "../../gameObjects/Enemy Objects/RangedEnemy.h"

//Hay que buscar una manera de pasar esto entre escenas y que se guarde
class EnemyGenerator : public Component {
private:
	//Referencias al player para hacer aparecer a los enemigos a su alrededor
	Transform* playerPos;
	Player* player;

	//Para saber la profundidad del jugador en el mapa de nodos,
	// cuando sale de la escena este deberia aumentar en una unidad
	int depth, nextSpawn, timePerWave, levelType;

	//Para agregar los enemigos a la escena de combate
	BattleScene* where;

	//Mockup de posible oleada
	const int* calcWave();
	void nextWave();
	void spawnWave(const int wave[3]);


public:
	static const int id = _ENEMY_GEN;
	EnemyGenerator(Player* pl, BattleScene* enemigos):player(pl), where(enemigos), depth(0), nextSpawn(0), timePerWave(0), levelType(0){
		playerPos = player->getComponent<Transform>();

		//empezamos en profundidad 0
		depth = 0;
	}

	virtual void initComponent();
	virtual void update();

	//Como hacer las oleadas?
	//Diversos metodos? que cada uno añada cosas distintas?
	//Quedaria un update muy complejo pero es lo que se me ocurre por ahora,
	//Dependiendo de la profundidad habra diversos casos con probabilidades distintas de que aparezcan
	//Tambien hay que poner un limite de enemigos que pueda haber a la vez, los gObjs disponibles son 100
	//Nos quedamos con 50 sabiendo que las balas tambien son gObjs? Alomejor nos quitan el limite ns

};