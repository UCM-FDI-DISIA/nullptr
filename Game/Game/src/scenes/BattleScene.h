#pragma once
#ifndef BATTLESCENE_H_
#define BATTLESCENE_H_

#include "GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/PlayerMovementComponent.h"

class BattleScene : public GameState {
private:
	GameObject* player;

public:
	BattleScene(SDLApplication* _game);
};

#endif