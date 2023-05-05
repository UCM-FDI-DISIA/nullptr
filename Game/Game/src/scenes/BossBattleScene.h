#pragma once
#include "BattleScene.h"
#include "../gameObjects/Enemy Objects/BossEnemy.h"
#include "../components/General Components/CallbackDelayer.h"
 
class BossBattleScene : public BattleScene {
private:
	BossEnemy* boss;
	GameObject* exitObject;
public:
	BossBattleScene(BattleType bt);

	void onBossDies();
};