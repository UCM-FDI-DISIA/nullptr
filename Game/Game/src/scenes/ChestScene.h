#pragma once
#include "GameState.h"
#include <utility>

class ChestScene : public GameState {
private:
	GameObject* gachaButton;
	AnimatorInfo* chestAI;
	pair<GameObject*, GameObject*> relic;
	pair<GameObject*, GameObject*> name;
  SoundEffect* chestOpening;
  
public:
	ChestScene();
	virtual ~ChestScene();

	void gacha(GameObject* obj);

	void spawnNewItem();

	void relicUI(Relic* relic);
	void relicImage(Relic* relic);
	void relicName(Relic* relic);
	void relicInfo(Relic* relic);

	// M�todos auxiliares
	void standarizeText(GameObject* g, int stat);
	string getEraString(string rEra);
	void createStat(int stat, string symbol, int yOffset);
};