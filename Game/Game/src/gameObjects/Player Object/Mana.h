#pragma once
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/Animator.h"
#include "../../core/PlayerData.h"

class Mana :public GameObject {

public:
	Mana(Vector2D pos);

	CallBack pickMana();
};