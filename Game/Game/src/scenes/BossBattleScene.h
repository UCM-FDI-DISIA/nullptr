#pragma once
#include "BattleScene.h"
#include "../gameObjects/Enemy Objects/BossEnemy.h"
 
class BossBattleScene : public BattleScene {
private:
	BossEnemy* boss;
public:
	BossBattleScene(BattleType bt);
};