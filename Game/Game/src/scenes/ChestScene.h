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
	void gacha(GameObject* obj);
	void spawnNewItem();
};