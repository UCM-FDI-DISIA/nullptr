#pragma once
#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "GameState.h"
#include "../components/General Components/Transform.h"
#include "../components/General Components/Image.h"
#include "../components/General Components/Animator.h"

class MainMenuScene : public GameState {
private:
public:
	MainMenuScene();
	static void play();
	static void options();
	static void album();
	static void exit();
};

#endif