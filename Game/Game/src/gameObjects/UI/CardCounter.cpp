#include "CardCounter.h"

CardCounter::CardCounter(Player* _p, int _t) {
	myPlayer = _p;
	type = _t;

	if (_t == 0) number = _p->getComponent<CardComponent>()->getDeckSize();
	else number = _p->getComponent<CardComponent>()->getPileSize();


}

