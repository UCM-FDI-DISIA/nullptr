#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "../core/GameObject.h"
#include "../data/constants.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Animator.h"
#include "../components/PlayerMovementComponent.h"
#include "../scenes/GameState.h"
#include "../components/CardComponent.h"
#include "../components/HeatlhComponent.h"
class SDLApplication;

class Player : public GameObject {
private:
	Transform* transform;
	Image* image;
	PlayerMovementComponent* playerMovementComponent;
	CardComponent* cardComponent;
	HealthComponent* health;
public:
	// Crea los componentes del jugador
	virtual void initGameObject(SDLApplication* _game);
};
#endif //!PLAYER_H_