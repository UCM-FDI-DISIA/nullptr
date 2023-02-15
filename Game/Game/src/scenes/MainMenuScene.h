#pragma once
#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Animator.h"
#include "../GameObjects/UI/Button.h"

class MainMenuScene : public GameState {
private:
public:
	MainMenuScene(SDLApplication* _game);
	static void play(SDLApplication* game);
	static void options(SDLApplication* game);
	static void album(SDLApplication* game);
	static void exit(SDLApplication* game);

	void createButtonAnimations(Animator* anim);
};

#endif