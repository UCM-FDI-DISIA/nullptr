#pragma once
#include "../core/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/PlayerMovementComponent.h"
#include "../core/SDLApplication.h"
class Player: public GameObject
{
public:
	Player(SDLApplication* game) {
		
		addComponent<Transform>(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(0, 0), WIN_WIDTH / 10, WIN_HEIGHT / 10);
		addComponent<Image>(game->getTexture("Player"));
		addComponent<PlayerMovementComponent>();
	}

};
