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
	// Abre la escena de shop
	static void shop();
	// Abre la escena de chest
	static void chest();
	// Vuelve a la escena de menú principal
	static void exit();
};

#endif