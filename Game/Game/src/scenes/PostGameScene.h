#pragma once
#include "GameState.h"

class PostGameScene : public GameState {
private:
	int damage, melee, ranged, tank, money;
	float time;

public:
	PostGameScene(int dmg, int mlee, int rngd, int tnk, int mny, float tm) : damage(dmg), melee(mlee), ranged(rngd), tank(tnk), money(mny), time(tm);
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
};