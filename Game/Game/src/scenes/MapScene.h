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
#include "../scenes/FuBattleScene.h"
#include "../scenes/PreBattleScene.h"
#include "../scenes/PaBattleScene.h"

class GameState;
class SDLApplication;
class Manager;

class MapScene : public  GameState {
private:
	Manager *manager = new Manager();
public:

	MapScene(SDLApplication* game);
	static void Pasado(SDLApplication* game);
	static void Presente(SDLApplication* game);
	static void Futuro(SDLApplication* game);
	static void Tienda(SDLApplication* game);
	static void Cofre(SDLApplication* game);
	static void Salir(SDLApplication* game);
};

#endif