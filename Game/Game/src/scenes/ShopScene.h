#pragma once
#ifndef SHOPSCENE_H_
#define SHOPSCENE_H_

#include "GameState.h"
class ShopScene : public GameState {
private:
public:
	ShopScene(SDLApplication* _game);
	static void mainMenu(SDLApplication* game);
};

#endif