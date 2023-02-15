#pragma once
#include "../core/Manager.h"
#include "../gameObjects/UI/Button.h"
#include "../core/SDLApplication.h"
#include "../scenes/ShopScene.h"
class GameState;
class SDLApplication;

class MapManager : public Manager {
public:
	MapManager(SDLApplication* game);
	static void Test1(SDLApplication* game);
	static void Test2(SDLApplication* game);
	static void Test3(SDLApplication* game);
	static void Test4(SDLApplication* game);
	static void Test5(SDLApplication* game);
};