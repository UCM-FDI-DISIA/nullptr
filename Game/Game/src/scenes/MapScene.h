#pragma once
#ifndef MAPSCENE_H_
#define MAPSCENE_H_

#include "GameState.h"

class Node;
class GameState;
class SDLApplication;

class MapScene : public GameState {
private:
	vector<Node*> const& nodeMap;
public:
	MapScene();
	static void pasado();
	static void presente();
	static void futuro();
	static void tienda();
	static void cofre();
	static void salir();
};

#endif