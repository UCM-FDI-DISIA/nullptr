#pragma once
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/Animator.h"
#include "../../core/PlayerData.h"

class Mana :public GameObject {

public:
	Mana(Vector2D pos) {
		addComponent<Transform>(pos+ (Vector2D(1, 0).rotate(rand() % 360) * MANA_OFFSET), VECTOR_ZERO, MANA_H, MANA_W, 0);
		addComponent<ColliderComponent>();
		addComponent<Animator>();
	}

	inline void pickMana() {
		PlayerData* pD = PlayerData::instance();
		pD->setCurrMana(pD->getCurrMana()+MANA_VALUE);
	}
};