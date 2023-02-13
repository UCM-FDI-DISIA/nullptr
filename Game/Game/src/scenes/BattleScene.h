#pragma once
#ifndef BATTLESCENE_H_
#define BATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Camera.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/PlayerMovementComponent.h"

class BattleScene : public GameState {
private:
	GameObject* player;
	Camera* camera;

public:
	// Constructora
	BattleScene(SDLApplication* _game);
	// Renderiza la escena dependiendo de la camara
	//virtual void render() const;
};

#endif