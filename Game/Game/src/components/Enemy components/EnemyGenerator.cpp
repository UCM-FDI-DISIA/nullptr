#include "EnemyGenerator.h"
#include "../../core/PlayerData.h"

void EnemyGenerator::initComponent() {
	int level = PlayerData::instance()->getLevel();
	levelType = (level == 1 ? level : (level < 5 ? 2 : 5));
	depth = level - levelType;
	timePerWave = STARTING_TIME_PER_WAVE - depth * 500;
}

void EnemyGenerator::update() {
	if (nextSpawn <= SDLApplication::instance()->getCurrentTime()) {
		nextWave();
	}
}

const int* EnemyGenerator::calcWave() {
	bool startingSpawns;
	switch (levelType)
	{
	case 1: 
		return WAVES[0];
	case 2:
		startingSpawns = true;
		break;
	case 5:
		startingSpawns = false;
		break;
	default:
		cout << "levelType erroneo";
		break;
	}

	int roll = rand() % 100;
	for (int i = 0; i < (startingSpawns ? 3 : 7); i++) {
		if (roll < (startingSpawns ? STARTING_SPAWNS[depth > 6 ? 6 : depth][i] : STANDARD_SPAWNS[depth][i])) return WAVES[i];
	}
}

void EnemyGenerator::nextWave() {
	spawnWave(calcWave());
	nextSpawn = SDLApplication::instance()->getCurrentTime() + timePerWave;
	if (depth < 29) depth += 1;
	timePerWave = STARTING_TIME_PER_WAVE - depth * 500;
}

void EnemyGenerator::spawnWave(const int wave[3]) {
	//Coger la posicion del player
	Vector2D spawn = playerPos->getCenter();

	//Hacemos un for y añadimos enemigos melee
	for (int i = 0; i < wave[0]; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * MELEE_RADIUS;
		GameObject* enemy = where->addGameObject<MeleeEnemy>(10, player, spawnPos);
		where->addEnemy(enemy);
	}
	//Hacemos un for y añadimos enemigos ranged
	for (int i = 0; i < wave[1]; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * RANGED_RADIUS;
		GameObject* enemy = where->addGameObject<RangedEnemy>(10, player, spawnPos);
		where->addEnemy(enemy);
	}
	//Hacemos un for y añadimos enemigos tank
	for (int i = 0; i < wave[2]; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * TANK_RADIUS;
		GameObject* enemy = where->addGameObject<MeleeEnemy>(10, player, spawnPos);
		where->addEnemy(enemy);
	}
}

