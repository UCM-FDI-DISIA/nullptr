#include "../core/Card.h"
#include "../scenes/BattleScene.h"
#pragma once

class GunCard : public Card {
	public:
		GunCard();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SwordCard : public Card {
	public:
		SwordCard();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class LaserShadesCard : public Card {
	public:
		LaserShadesCard();
		void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};