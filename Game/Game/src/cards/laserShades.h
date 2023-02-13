#include "../core/Card.h"
#pragma once

class LaserShades : public Card {
	public:
		LaserShades();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult);
};