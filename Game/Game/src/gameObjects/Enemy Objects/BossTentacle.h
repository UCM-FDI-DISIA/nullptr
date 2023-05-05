#pragma once
#include "../GameObject.h"
#include "../../data/constants.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/Animator.h"
#include "../../components/Enemy components/TentacleBehaviour.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../core/SDLApplication.h"
class BossTentacle:public GameObject
{
private:
	int damage = 25;
public:
	virtual void initGameObject(Transform* boss);
};