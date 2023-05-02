#pragma once
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/Animator.h"
#include "../../data/PlayerData.h"

class Mana :public GameObject {
private:
	SoundEffect* manaPickSound;

public:
	
	virtual void initGameObject(Vector2D pos);

	CallBackCol pickMana();
};