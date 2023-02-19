#pragma once
#ifndef MAPSCENE_H_
#define MAPSCENE_H_

#include "GameState.h"

class MapScene : public GameState {
private:
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