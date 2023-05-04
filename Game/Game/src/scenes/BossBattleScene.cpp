#include "BossBattleScene.h"

BossBattleScene::BossBattleScene(BattleType bt) : BattleScene(bt) {
	// Creamos el boss
	Transform* pltr = player->getComponent<Transform>();
	boss= addGameObject<BossEnemy>(_grp_ENEMIES, pltr->getPos() + BOSS_OFFSET, BOSS_LIFE, player, [&]() {onBossDies(); });

	enemyGenerator->getComponent<EnemyGenerator>()->setCanSpawn(false);
}

void BossBattleScene::onBossDies() {
	// Se debe pasar a la escena de cinematica
	/*exitObject = addGameObject();
	exitObject->addComponent<CallbackDelayer>();*/
}