#pragma once
#include "GameState.h"

class PauseMenuScene : public GameState {
private:
public:
	PauseMenuScene();

	void handleInput() override;
};