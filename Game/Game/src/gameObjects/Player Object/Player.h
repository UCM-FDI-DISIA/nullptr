#pragma once
#include "../GameObject.h"
#include "../../data/constants.h"
#include "../../components/General Components/Transform.h"
#include "../../components/Player components/PlayerAnimator.h"
#include "../../components/Player components/PlayerMovementComponent.h"
#include "../../scenes/GameState.h"
#include "../../components/Card Components/CardComponent.h"
#include "../../components/General Components/HealthComponent.h"
#include "../../components/General Components/EffectController.h"

class Player : public GameObject {
private:
	Transform* transform;
	PlayerMovementComponent* playerMovementComponent;
	PlayerAnimator* animator;
	CardComponent* cardComponent;
	HealthComponent* health;
	EffectController* effectController;

public:
	// Crea los componentes del jugador
	virtual void initGameObject();
};