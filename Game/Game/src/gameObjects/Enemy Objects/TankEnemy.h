#pragma once
#include "../GameObject.h"
#include "../../data/constants.h"
#include "../../components/Enemy components/TankBehaviour.h"
#include "../../components/General Components/Transform.h"
#include "../../components/Enemy components/EnemyAnimator.h"
#include "../../core/SDLApplication.h"

class TankEnemy : public GameObject {
private:
public:
	virtual void initGameObject(Vector2D pos, int life, Player* player);
};