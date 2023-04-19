#pragma once
#include "GameState.h"

class PostGameState : public GameState {
private:
public:
	PostGameState();
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
};