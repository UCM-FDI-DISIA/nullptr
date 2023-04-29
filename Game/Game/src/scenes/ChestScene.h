#pragma once
#include "NodeScene.h"
#include <utility>

class ChestScene : public NodeScene {
private:
	GameObject* gachaButton;
	AnimatorInfo* chestAI;
	pair<GameObject*, GameObject*> relic;
	pair<GameObject*, GameObject*> name;
	pair<GameObject*, vector<GameObject*>> stats;

public:
	ChestScene();
	virtual ~ChestScene();

	void gacha(GameObject* obj);

	void spawnNewItem();

	void relicUI(Relic* relic);
	void relicImage(Relic* relic);
	void relicName(Relic* relic, SDL_Color color);
	void relicInfo(Relic* relic, SDL_Color color);
	void standarizeText(GameObject* g, int stat, SDL_Color color);
};