#pragma once

#include "../Player.h"

class CardCounter : public GameObject {
private:
	Player* myPlayer;
	int number;
	int type;
public:
	CardCounter() : GameObject(), number(0), myPlayer(nullptr), type(0) { }
	CardCounter(Player* _p, int _t);
	virtual void update();
	virtual void render() const;
};