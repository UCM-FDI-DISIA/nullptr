#pragma once
#include "../GameObject.h"
#include "../../data/constants.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/Animator.h"
#include "../../core/SDLApplication.h"

class BossEnemy :public GameObject
{
public:
	virtual void initGameObject(Vector2D pos, int life, Player* player, CallBack cb);
};
