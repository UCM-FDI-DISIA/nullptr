#pragma once
#ifndef CHESTSCENE_H_
#define CHETSSCENE_H_

#include "GameState.h"

class ChestScene : public GameState {
private:
public:
	ChestScene();
	static void mainMenu();
	void gacha(GameObject* obj);
};

#endif