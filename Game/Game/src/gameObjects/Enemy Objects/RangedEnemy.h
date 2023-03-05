// cleon says: don't be afraid. fuera 1 de los 2. confiad en vuestros instintos. padawans.

#pragma once
#ifndef RANGED_H_
#define RANGED_H_
#include "../GameObject.h"
#include "../../data/constants.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/Animator.h"
#include "../../core/SDLApplication.h"
class SDLApplication;
class RangedEnemy:public GameObject
{
public:
	virtual void initGameObject(Vector2D pos, int life, Player* player);
};
#endif

