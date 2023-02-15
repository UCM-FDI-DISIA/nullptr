#pragma once
#ifndef RANGED_H_
#define RANGED_H_
#include "../core/GameObject.h"
#include "../data/constants.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Animator.h"
#include "../core/SDLApplication.h"
class SDLApplication;
class RangedEnemy:public GameObject
{
public:
	RangedEnemy(SDLApplication* game, Vector2D pos, Vector2D vel, int life, Player* player, GameState* scene, Transform* camera);
	
};
#endif

