#pragma once

#include "NodeScene.h"

class ChestScene : public NodeScene {
private:
	bool alreadyClicked = false;
public:
	ChestScene();
	void gacha(GameObject* obj);

	void spawnNewItem();
};