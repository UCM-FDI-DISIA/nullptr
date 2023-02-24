#include "../core/Card.h"
#include "../scenes/BattleScene.h"
#pragma once

class GunCard : public Card {
	public:
		GunCard() : Card(10,6,35,0.5,0.005,"Pistola","Dispara de manera normal",
			"Se disparan todas las balas como una escopeta", SDLApplication::getTexture("Pistol")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SwordCard : public Card {
	public:
		SwordCard() : Card(20, 5, 80, 2, 0.5, "Espada", "", "", SDLApplication::getTexture("Sword")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class LaserShadesCard : public Card {
	public:
		LaserShadesCard() : Card(20, 5, 80, 2, 0.5, "Gafas Láser", "", "", SDLApplication::getTexture("LaserGlasses")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};