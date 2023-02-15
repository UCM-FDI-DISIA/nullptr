#include "../core/Card.h"
#pragma once

class Gun : public Card {
	public:
		Gun();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult);
};

class Sword : public Card {
	public:
		Sword();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult);
};

class LaserShades : public Card {
	public:
		LaserShades();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult);
};