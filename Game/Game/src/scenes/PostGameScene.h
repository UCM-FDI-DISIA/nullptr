#pragma once
#include "GameState.h"

class PostGameScene : public GameState {
private:
	int damage, melee, ranged, tank, money;
	float time;
	string timeText;
	pair<CardId,int> newCard;

	int nextEvent;
	float coolDown;

	void showObject();
	void showPlayer();
	void showCard();

public:
	PostGameScene(int dmg, int mlee, int rngd, int tnk, int mny, float tm);
	void update() override;
};