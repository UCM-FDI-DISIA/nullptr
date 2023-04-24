#pragma once
#include "GameState.h"

class PostGameScene : public GameState {
private:
	int damage, melee, ranged, tank, money;
	float time;
	pair<CardId,int> newCard;

public:
	PostGameScene(int dmg, int mlee, int rngd, int tnk, int mny, float tm);
};