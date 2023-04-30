#include "BossBattleScene.h"

BossBattleScene::BossBattleScene(BattleType bt) : BattleScene(bt) {
	// Creamos el boss
	Vector2D spawnPos = player->getComponent<Transform>()->getCenter() + Vector2D(1, 0).rotate(rand() % 360) * TANK_RADIUS;
	spawnPos = enemyGenerator->getComponent<EnemyGenerator>()->checkPos(spawnPos, TANK_RADIUS);
	boss= addGameObject<BossEnemy>(_grp_ENEMIES, spawnPos, 10000, player, [&]() {onBossDies(); });

	enemyGenerator->getComponent<EnemyGenerator>()->setCanSpawn(false);
}

void BossBattleScene::onBossDies() {
	// Se debe pasar a la escena de cinematica
	/*exitObject = addGameObject();
	exitObject->addComponent<CallbackDelayer>();*/
}