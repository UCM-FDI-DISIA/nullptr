#pragma once
#include "NodeScene.h"

class ChestScene : public NodeScene {
private:
	bool alreadyClicked = false;
	GameObject* gachaButton;
	AnimatorInfo* chestAI;
	SoundEffect* chestOpening;
public:
	ChestScene();
	virtual ~ChestScene();
	static void mainMenu();
	void gacha(GameObject* obj);
	void spawnNewItem();
};