#include "EnemyGenerator.h"

void EnemyGenerator::update() {
	if (nextSpawn <= SDLApplication::instance()->getCurrentTime()) {
		nextWave();
	}
}

void EnemyGenerator::nextWave() {
	spawnWave(1, 1, 1);
	nextSpawn = SDLApplication::instance()->getCurrentTime() + timePerWave;
}

void EnemyGenerator::spawnWave(int melee, int ranged, int tank) {
	//Coger la posicion del player
	Vector2D spawn = playerPos->getPos();

	//Hacemos un for y añadimos enemigos melee
	for (int i = 0; i < melee; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * radius;
		GameObject* enemy = where->addGameObject<MeleeEnemy>(10, player, spawnPos);
		where->addEnemy(enemy);
	}
	//Hacemos un for y añadimos enemigos ranged
	for (int i = 0; i < ranged; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * radius;
		GameObject* enemy = where->addGameObject<RangedEnemy>(10, player, spawnPos);
		where->addEnemy(enemy);
	}
	//Hacemos un for y añadimos enemigos tank
	for (int i = 0; i < tank; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * radius;
		GameObject* enemy = where->addGameObject<MeleeEnemy>(10, player, spawnPos);
		where->addEnemy(enemy);
	}
}

