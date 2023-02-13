#pragma once
#pragma once
#include "../core/Manager.h"
class GameState;
class SDLApplication;

class MainMenuManager : public Manager {
public:
	MainMenuManager(SDLApplication* game);
	static void Test(SDLApplication* game);
};