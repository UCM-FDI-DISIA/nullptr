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
	// Abre la escena de batalla en el pasado
	static void pasado();
	// Abre la escena de batalla en el presente
	static void presente();
	// Abre la escena de batalla en el furuto
	static void futuro();
	// Abre la escena de tienda
	static void tienda();
	// Abre la escena de cofre
	static void cofre();
	// Vuelve a la escena de menú principal
	static void salir();
};

#endif