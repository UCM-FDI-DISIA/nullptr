#pragma once
#include "../core/Manager.h"
class GameState;
class SDLApplication;
typedef void CallBack();

class MainSceneManager : public Manager {
public:
	MainSceneManager(CallBack _c, SDLApplication* game);
};

