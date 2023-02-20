#pragma once

#include "GameState.h"

class SDLApplication;
class GameOverScene : public GameState {
public:
	GameOverScene();
	static void mainMenu();
};