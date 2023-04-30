#pragma once
#include "GameState.h"
#include "../gameObjects/Node Objects/Node.h"

class GameOverScene : public GameState {
private:
	SoundEffect* deathSound;
	BattleType previousBT;
public:
	GameOverScene(BattleType prevBt, bool cameFromTutorial = false);
	virtual ~GameOverScene();
};