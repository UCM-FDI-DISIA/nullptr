#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "../core/GameObject.h"
#include "../data/constants.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/PlayerMovementComponent.h"
class SDLApplication;

class Player : public GameObject {
public:
	// Constructoras
	Player(SDLApplication* _game);
	Player(SDLApplication* _game, const Vector2D& _center);

};
#endif //!PLAYER_H_