#pragma once
#ifndef OPTIONSMENUSCENE_H_
#define OPTIONSMENUSCENE_H_

#include "GameState.h"

class SDLApplication;
class OptionsMenuScene : public GameState {
private:
public:
	OptionsMenuScene(SDLApplication* _game);
	static void mainMenu(SDLApplication* _game);
};

#endif