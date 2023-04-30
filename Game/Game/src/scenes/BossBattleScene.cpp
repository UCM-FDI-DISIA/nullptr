#include "BossBattleScene.h"

BossBattleScene::BossBattleScene(BattleType bt) : BattleScene(bt) {
	// Creamos el boss
	Vector2D spawnPos = player->getComponent<Transform>()->getCenter() + Vector2D(1, 0).rotate(rand() % 360) * TANK_RADIUS;
	spawnPos = enemyGenerator->getComponent<EnemyGenerator>()->checkPos(spawnPos, TANK_RADIUS);
	boss= addGameObject<BossEnemy>(_grp_ENEMIES, spawnPos, 10, player);

	enemyGenerator->getComponent<EnemyGenerator>()->setCanSpawn(false);
}