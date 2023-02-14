#pragma once
#pragma once
#include "../core/Manager.h"
class GameState;
class SDLApplication;

class MainMenuManager : public Manager {
public:
	MainMenuManager(SDLApplication* game);
	static void play(SDLApplication* game);
	static void options(SDLApplication* game);
	static void album(SDLApplication* game);
	static void exit(SDLApplication* game);
};