#include "../Card Objects/Card.h"
#include "../../scenes/BattleScene.h"
#pragma once

class GunCard : public Card {
	public:
		GunCard() : Card(10, 6, 35, 0.5, "Pistola$Dispara de manera normal&Se disparan todas las balas como una escopeta", 
			SDLApplication::getTexture("Pistol")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SwordCard : public Card {
	public:
		SwordCard() : Card(20, 5, 80, 0.5, "Espada", SDLApplication::getTexture("Sword")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class LaserShadesCard : public Card {
	public:
		LaserShadesCard() : Card(20, 5, 80, 1, "Gafas Láser", SDLApplication::getTexture("LaserGlasses")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class PulgaCard : public Card {
public:
	PulgaCard() : Card(30, 2, 30, 1.5, "Pulga", SDLApplication::getTexture("Tick")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult ,BattleScene* where );
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SpearCard : public Card {
public:
	SpearCard() : Card(15, 6, 15, 0.75, "Lanza", SDLApplication::getTexture("Spear")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SMGCard : public Card {
public:
	SMGCard() : Card(3, 40, 60, SMG_CADENCE, "SMG", SDLApplication::getTexture("SMG")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};