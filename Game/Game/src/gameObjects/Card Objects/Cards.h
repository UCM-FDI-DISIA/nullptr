#include "../Card Objects/Card.h"
#include "../../scenes/BattleScene.h"
#pragma once

class GunCard : public Card {
	public:
		constexpr static cardId_type id = _card_GUN;

		GunCard() : Card(cardsData().get("Pistola")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SwordCard : public Card {
	public:
		constexpr static cardId_type id = _card_SWORD;

		SwordCard() : Card(cardsData().get("Espada")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class TorchCard : public Card {
public:
	constexpr static cardId_type id = _card_TORCH;

	TorchCard() : Card(cardsData().get("Antorcha")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class LaserShadesCard : public Card {
	public:
		constexpr static cardId_type id = _card_LASERGLASSES;

		LaserShadesCard() : Card(cardsData().get("Gafas Laser")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class BowCard : public Card {
public:
	constexpr static cardId_type id = _card_BOW;

	BowCard() : Card(cardsData().get("Arco")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class PulgaCard : public Card {
public:
	constexpr static cardId_type id = _card_PULGA;

	PulgaCard() : Card(cardsData().get("Pulga")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult ,BattleScene* where );
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SpearCard : public Card {
public:
	constexpr static cardId_type id = _card_SPEAR;

	SpearCard() : Card(cardsData().get("Lanza")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SMGCard : public Card {
public:
	constexpr static cardId_type id = _card_SMG;

	SMGCard() : Card(cardsData().get("SMG")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  AssaultRifleCard : public Card {
public:
	constexpr static cardId_type id = _card_ASSAULTRIFLE;

	AssaultRifleCard() : Card(cardsData().get("Rifle de asalto")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  LightRifleCard: public Card {
public:
	constexpr static cardId_type id = _card_LIGHTRIFLE;

	LightRifleCard() : Card(cardsData().get("Rifle de luz")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  MegaphoneCard : public Card {
public:
	constexpr static cardId_type id = _card_MEGAPHONE;

	MegaphoneCard() : Card(cardsData().get("Megafono")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  RiotShieldCard : public Card {
public:
	constexpr static cardId_type id = _card_RIOTSHIELD;

	RiotShieldCard() : Card(cardsData().get("Escudo Antidisturbios")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	void checkCollisionWithBullets(GameObject* shield, BattleScene* where);
};
class  CheatGunCard : public Card {
public:
	CheatGunCard() : Card(cardsData().get("Cheat Gun")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class RitualAxeCard : public Card {
private:
	int enemiesKilled;
public:
	RitualAxeCard() : Card(cardsData().get("Hacha Ritual")) { enemiesKilled = 0; };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	void enemieKilled();
};