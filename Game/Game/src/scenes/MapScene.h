#pragma once
#ifndef MAPSCENE_H_
#define MAPSCENE_H_

#include "GameState.h"
#include "../managers/MapManager.h"
#include "../core/Manager.h"
#include "../gameObjects/UI/Button.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/UI/Button.h"
#include "../core/SDLApplication.h"
#include "../scenes/ChestScene.h"
#include "../scenes/ShopScene.h"
#include "../scenes/BattleScene.h"


class GameState;
class SDLApplication;
class Manager;

class MapScene : public  GameState {
private:
	Manager *manager = new Manager();
public:

	MapScene(SDLApplication* game);
	static void pasado(SDLApplication* game);
	static void presente(SDLApplication* game);
	static void futuro(SDLApplication* game);
	static void tienda(SDLApplication* game);
	static void cofre(SDLApplication* game);
	static void salir(SDLApplication* game);
};

#endif