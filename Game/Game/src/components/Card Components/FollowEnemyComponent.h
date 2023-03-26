#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include "../General Components/HealthComponent.h"
#include "../../gameObjects/GameObject.h"
#include <vector>



class FollowEnemyComponent : public Component
{
private:
	Transform* tr;
	Transform* enemy;
	float followStartTime;
	Transform* findClosestEnemy();
public:
	static const int id = _FOLLOW_ENEMY_COMPONENT;
	FollowEnemyComponent(float time) : tr(nullptr), enemy(nullptr), followStartTime(time){}
	
	void update() override;
	void initComponent() override;
};