#pragma once
#include "GameState.h"
class CinematicScene : public GameState {
private:
	Animator* animator;
	CallBack onComplete_;
public:
	CinematicScene(string textureKey, int fw, int fh, int r, int c, Animation cinematic, CallBack onComplete);

	void update() override;
};

