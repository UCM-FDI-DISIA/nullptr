#pragma once
#include "../core/Manager.h"
class GameState;
class SDLApplication;

class MainSceneManager : public Manager {
public:
	MainSceneManager(SDLApplication* game);
	static void Test(SDLApplication* game);
};

