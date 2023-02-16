#include "../core/Card.h"
#pragma once

class GunCard : public Card {
	public:
		GunCard();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult);
};

class SwordCard : public Card {
	public:
		SwordCard();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult);
};

class LaserShadesCard : public Card {
	public:
		LaserShadesCard();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult);
};