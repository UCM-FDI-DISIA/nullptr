#pragma once
#ifndef MELEE_H_
#define MELEE_H_
#include "../../components/Enemy components/MeleeBehaviour.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../GameObject.h"
#include "../../data/constants.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/Animator.h"
#include "../../scenes/GameState.h"

class SDLApplication;
class MeleeEnemy :public GameObject
{
public:
	virtual void initGameObject(Vector2D pos, int life, Player* player);
};
#endif

