#pragma once
#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Animator.h"

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