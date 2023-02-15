#pragma once
#ifndef MELEE_H_
#define MELEE_H_
#include "../components/MeleeBehaviour.h"
#include "../components/ColliderComponent.h"
#include "../core/GameObject.h"
#include "../data/constants.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Animator.h"
#include "../scenes/GameState.h"

class SDLApplication;
class MeleeEnemy :public GameObject
{
public:
	MeleeEnemy(SDLApplication* game, Vector2D pos, Vector2D vel, int life, Player* player, Transform* camera);
	
};
#endif

