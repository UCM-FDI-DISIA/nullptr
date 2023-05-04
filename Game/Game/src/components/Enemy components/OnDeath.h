#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../gameObjects/GameObject.h"
#include "../../scenes/BattleScene.h"
#include "../../gameObjects/Player Object/Mana.h"
#include "../../gameObjects/Enemy Objects/SpacialEter.h"
#include "../../gameObjects/Enemy Objects/DeathAnimation.h"
#include "../../components/General Components/StatsTrackComponent.h"

enum EnemyType
{
	meleeEnemy = 0,
	rangedEnemy,
	tankEnemy, 
	assasinEnemy
};

class OnDeath : public Component {
private:
	Transform* enemyTransform;
	Transform* playerTransform;
	int numMana, numEter;
	SoundEffect* deathSound;
	CallBack finalFunction;
	int type;
public:
	static const int id = _ON_DEATH;

	OnDeath( int numMana, int numEter, Transform* player, CallBack cb = nullptr) : 
		numMana(numMana), numEter(numEter), playerTransform(player), enemyTransform(nullptr), finalFunction(cb) {};

	virtual void initComponent();
	void death();
	void deathAnim();
};