#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../gameObjects/GameObject.h"
#include "../../scenes/BattleScene.h"

class OnDeath : public Component {
private:
	Transform* enemyData;
	GameObject* mana,* eter;
	int numMana, numEter;
	BattleScene* where;
public:
	static const int id = _ON_DEATH;

	OnDeath(GameObject* mana, GameObject* eter, int numMana, int numEter):
	mana(mana),eter(eter), numMana(numMana), numEter(numEter){};

	virtual void initComponent();
	void death();
};