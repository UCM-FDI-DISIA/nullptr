#pragma once
#pragma once
#include "../GameObject.h"
#include "../../data/constants.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/Animator.h"
#include "../../components/Enemy components/TargetedComponent.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../core/SDLApplication.h"
class TargetedTentacle: public GameObject
{
public:
	virtual void initGameObject(Vector2D pos, Transform* player, bool imagen);

private:
	int damage = 30;
};
