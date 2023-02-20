#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "../core/GameObject.h"
#include "../data/constants.h"
#include "../components/Transform.h"
#include "../components/PlayerAnimator.h"
#include "../components/PlayerMovementComponent.h"
#include "../scenes/GameState.h"
#include "../components/CardComponent.h"
#include "../components/HeatlhComponent.h"

class SDLApplication;
class BattleScene;

class Player : public GameObject {
private:
	Transform* transform;
	PlayerMovementComponent* playerMovementComponent;
	PlayerAnimator* animator;
	CardComponent* cardComponent;
	HealthComponent* health;
public:
	// Crea los componentes del jugador
	virtual void initGameObject();
};
#endif //!PLAYER_H_