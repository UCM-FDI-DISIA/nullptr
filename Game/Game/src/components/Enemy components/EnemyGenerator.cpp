#include "EnemyGenerator.h"
#include "../../core/PlayerData.h"

void EnemyGenerator::initComponent() {
	int level = PlayerData::instance()->getLevel();
	playerPos = player->getComponent<Transform>();
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


//Funcion que comprueba que la posicion de spawn es correcta
//Reduce el circulo de spawn dependiendo de donde se salga el enemigo spawneado
Vector2D EnemyGenerator::checkPos(Vector2D pos, const int rad) {
	
	//Si no esta fuera de los limites del mapa
    if (pos.getX() < FLOOR_WIDTH - ENEMY_WIDTH && pos.getX() > ENEMY_WIDTH && pos.getY() < FLOOR_HEIGHT - ENEMY_HEIGHT && pos.getY() > ENEMY_HEIGHT) {
		return pos;
	}

	//Si esta fuera por la derecha
	if (pos.getX() > FLOOR_WIDTH - ENEMY_WIDTH) {
		if (pos.getY() > FLOOR_HEIGHT - ENEMY_HEIGHT) {
			//esquina inferior derecha 90-180
			return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(90 + rand() % 90) * rad);
		}
		if (pos.getY() < ENEMY_HEIGHT) {
			//esquina superior derecha 180-270
			return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(180 + rand() % 90) * rad);
			
		}

		// Pared derecha 90-270
		return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(90 + rand() % 180) * rad);
	}

	//Si esta fuera por la izquierda
	if (pos.getX() < ENEMY_WIDTH) {
		if (pos.getY() > FLOOR_HEIGHT - ENEMY_HEIGHT) {
			// esquina inferior izquierda 0-90
			return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate( rand() % 90) * rad);
		}
		if (pos.getY() < ENEMY_HEIGHT) {
			//esquina superior izquierda 270-360
			return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(270 + rand() % 90) * rad);
		}

		// pared izquierda 270-450
		return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(270 + rand() % 180) * rad);
	}

	//Si esta fuera por abajo
	if (pos.getY() < ENEMY_HEIGHT) {
		//pared superior 180-360
		return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(180 + rand() % 180) * rad);
		
	}

	//Si esta fuera por arriba
	//pared inferior 0-180 
	return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(rand() % 180) * rad);
	
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

	//Hacemos un for y a�adimos enemigos melee
	for (int i = 0; i < wave[0]; i++) {
		
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * MELEE_RADIUS;
		spawnPos = checkPos(spawnPos, MELEE_RADIUS);
		GameObject* enemy = where->addGameObject<MeleeEnemy>(spawnPos,10, player);
		where->addEnemy(enemy);
	}
	//Hacemos un for y a�adimos enemigos ranged
	for (int i = 0; i < wave[1]; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * RANGED_RADIUS;
		spawnPos = checkPos(spawnPos, RANGED_RADIUS);
		//CAMBIAR POR RANGED ENEMY CUANDO FUNCIONE BIEN EL LIFETIME COMPONENT
		GameObject* enemy = where->addGameObject<MeleeEnemy>(spawnPos, 10, player);
		where->addEnemy(enemy);
	}
	//Hacemos un for y a�adimos enemigos tank
	for (int i = 0; i < wave[2]; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * TANK_RADIUS;
		spawnPos = checkPos(spawnPos, TANK_RADIUS);

		//CAMBIAR POR TANK ENEMY CUANDO EXISTA
		GameObject* enemy = where->addGameObject<MeleeEnemy>(spawnPos, 10, player);
		where->addEnemy(enemy);
	}
}

