#pragma once
#include "../core/Manager.h"
class GameState;
class SDLApplication;

class MapManager : public Manager {
public:
	MapManager(SDLApplication* game);
	static void Test(SDLApplication* game);
};

