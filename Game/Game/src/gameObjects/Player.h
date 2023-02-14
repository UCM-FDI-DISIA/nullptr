#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "../core/GameObject.h"
#include "../data/constants.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/PlayerMovementComponent.h"
#include "../scenes/GameState.h"
class SDLApplication;

class Player : public GameObject {
private:
	Transform* transform;
	Image* image;
	PlayerMovementComponent* playerMovementComponent;
public:
	// Constructora
	Player(SDLApplication* _game);
};
#endif //!PLAYER_H_