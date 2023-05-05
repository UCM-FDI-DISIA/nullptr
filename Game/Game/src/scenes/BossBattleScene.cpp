#include "BossBattleScene.h"

BossBattleScene::BossBattleScene(BattleType bt) : BattleScene(bt) {
	// Creamos el boss
	Transform* pltr = player->getComponent<Transform>();
	boss= addGameObject<BossEnemy>(_grp_ENEMIES, pltr->getPos() + BOSS_OFFSET, BOSS_LIFE, player, [&]() {onBossDies(); });

	enemyGenerator->getComponent<EnemyGenerator>()->setCanSpawn(false);
}

void BossBattleScene::onBossDies() {
	// Se pasa a la escena de cinematica
	SDLApplication::newScene<CinematicScene>(CINEMATIC_FINAL_NAME, CINEMATIC_WIDTH, CINEMATIC_HEIGHT, CINEMATIC_FINAL_ROWS, CINEMATIC_FINAL_COLS, CINEMATIC_FINAL_ANIMATION,
	[]() {
		SDLApplication::newScene<MainMenuScene>();
	});
}