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

    Vector2D checkPos(Vector2D pos, const int rad);


public:
	static const int id = _ENEMY_GEN;
	EnemyGenerator(Player* pl, BattleScene* enemigos) :player(pl), playerPos(nullptr), where(enemigos), depth(0), nextSpawn(0), timePerWave(0), levelType(0) {};

	
	virtual void initComponent();
	virtual void update();



};