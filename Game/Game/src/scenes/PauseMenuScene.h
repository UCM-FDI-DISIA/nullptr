#pragma once
#ifndef PAUSEMENUSCENE_H_
#define PAUSEMENUSCENE_H_

#include "GameState.h"
class PauseMenuScene : public GameState {
private:
public:
	PauseMenuScene();
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
};

#endif