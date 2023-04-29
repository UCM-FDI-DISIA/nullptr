#pragma once
#include "GameState.h"

class GameOverScene : public GameState {
private:
	SoundEffect* deathSound;
public:
	GameOverScene(bool cameFromTutorial = false);
	virtual ~GameOverScene();
};