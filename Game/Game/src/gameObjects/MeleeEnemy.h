#pragma once
#ifndef MELEE_H_
#define MELEE_H_
#include "../components/MeleeBehaviour.h"
#include "../components/ColliderComponent.h"
#include "../core/GameObject.h"
#include "../data/constants.h"
#include "../components/Transform.h"
#include "../components/Image.h"
//#include "../components/Animator.h"
#include "../scenes/GameState.h"
#include "../components/EnemyAnimator.h"

class SDLApplication;
class MeleeEnemy :public GameObject
{
private:

	PlayerAnimator* animator;

public:
	virtual void initGameObject(Vector2D pos, int life, Player* player);
};
#endif

