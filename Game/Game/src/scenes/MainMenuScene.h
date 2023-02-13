#pragma once
#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
class MainMenuScene : public GameState {
private:
public:
	MainMenuScene(SDLApplication* _game);
};

#endif