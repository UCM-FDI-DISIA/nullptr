#pragma once
#ifndef OPTIONSMENUSCENE_H_
#define OPTIONSMENUSCENE_H_

#include "GameState.h"

class SDLApplication;
class OptionsMenuScene : public GameState {
private:
public:
	OptionsMenuScene();
	static void mainMenu();
	static void toggleScreen();
};

#endif