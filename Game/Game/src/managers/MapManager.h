#pragma once
#include "../core/Manager.h"
class GameState;
class SDLApplication;

class MapManager : public Manager {
public:
	MapManager(SDLApplication* game);
	static void Test1(SDLApplication* game);
	static void Test2(SDLApplication* game);
	static void Test3(SDLApplication* game);
};