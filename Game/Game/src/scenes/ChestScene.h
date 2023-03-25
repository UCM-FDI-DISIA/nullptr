#pragma once
#ifndef CHESTSCENE_H_
#define CHETSSCENE_H_

#include "NodeScene.h"

class ChestScene : public NodeScene {
private:
	bool alreadyClicked = false;
public:
	ChestScene();
	static void mainMenu();
	void gacha(GameObject* obj);

	void spawnNewItem();

	
};

#endif