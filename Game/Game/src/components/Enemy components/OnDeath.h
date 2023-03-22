#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../gameObjects/GameObject.h"
#include "../../scenes/BattleScene.h"
#include "../../gameObjects/Player Object/Mana.h"
#include "../../gameObjects/Enemy Objects/SpacialEter.h"

class OnDeath : public Component {
private:
	Transform* enemyTransform;
	Transform* playerTransform;
	int numMana, numEter;
public:
	static const int id = _ON_DEATH;

	OnDeath( int numMana, int numEter, Transform* player): numMana(numMana), numEter(numEter), playerTransform(player){};

	virtual void initComponent();
	void death();
};