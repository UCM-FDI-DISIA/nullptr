#pragma once
#ifndef MAPSCENE_H_
#define MAPSCENE_H_

#include "GameState.h"

class MapScene : public GameState {
private:
public:
	MapScene(SDLApplication* _game);
	static void Test(SDLApplication* game);
};

#endif