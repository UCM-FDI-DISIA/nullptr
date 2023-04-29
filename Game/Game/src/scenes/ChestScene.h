#pragma once
#include "NodeScene.h"
#include <utility>

class ChestScene : public NodeScene {
private:
	GameObject* gachaButton;
	AnimatorInfo* chestAI;
	pair<GameObject*, GameObject*> relic;
	pair<GameObject*, GameObject*> name;
  SoundEffect* chestOpening;
  
public:
	void gacha(GameObject* obj);

	void spawnNewItem();

	void relicUI(Relic* relic);
	void relicImage(Relic* relic);
	void relicName(Relic* relic, SDL_Color color);
	void relicInfo(Relic* relic, SDL_Color color);

	// M�todos auxiliares
	void standarizeText(GameObject* g, int stat, SDL_Color color);
	string getEraString(string rEra);
	void createStat(int stat, string symbol, int yOffset, SDL_Color color);
};