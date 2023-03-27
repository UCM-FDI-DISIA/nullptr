#pragma once
#ifndef CHESTSCENE_H_
#define CHETSSCENE_H_

#include "NodeScene.h"

class ChestScene : public NodeScene {
private:
	bool alreadyClicked = false;
	GameObject* gachaButton;
	AnimatorInfo* chestAI;
public:
	ChestScene();
	~ChestScene();
	static void mainMenu();
	void gacha(GameObject* obj);

	void spawnNewItem();

	
};

#endif