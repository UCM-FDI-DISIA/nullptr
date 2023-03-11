#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../gameObjects/GameObject.h"
#include "../../scenes/BattleScene.h"
#include "../../gameObjects/Player Object/Mana.h"

class OnDeath : public Component {
private:
	Transform* enemyData;
	int numMana, numEter;
	BattleScene* where;
public:
	static const int id = _ON_DEATH;

	OnDeath( int numMana, int numEter, BattleScene* batalla): numMana(numMana), numEter(numEter), where(batalla){};

	virtual void initComponent();
	void death();
};