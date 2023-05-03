#include "BossBattleScene.h"

BossBattleScene::BossBattleScene(BattleType bt) : BattleScene(bt) {
	// Creamos el boss
	Transform* pltr = player->getComponent<Transform>();
	boss= addGameObject<BossEnemy>(_grp_ENEMIES, pltr->getPos() + Vector2D(BOSS_ENEMY_WIDTH/2, - BOSS_ENEMY_HEIGHT /2), 100, player, [&]() {onBossDies(); });

	enemyGenerator->getComponent<EnemyGenerator>()->setCanSpawn(false);
}

void BossBattleScene::onBossDies() {
	// Se debe pasar a la escena de cinematica
	/*exitObject = addGameObject();
	exitObject->addComponent<CallbackDelayer>();*/
}