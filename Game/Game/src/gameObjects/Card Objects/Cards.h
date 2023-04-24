#include "../Card Objects/Card.h"
#include "../../scenes/BattleScene.h"
#pragma once

class GunCard : public Card {
	public:
		constexpr static cardId_type id = _card_GUN;

		GunCard() : Card(cardsData().get("Gun")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SwordCard : public Card {
	public:
		constexpr static cardId_type id = _card_SWORD;

		SwordCard() : Card(cardsData().get("Sword")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class TorchCard : public Card {
public:
	constexpr static cardId_type id = _card_TORCH;

	TorchCard() : Card(cardsData().get("Torch")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class LaserShadesCard : public Card {
	public:
		constexpr static cardId_type id = _card_LASERGLASSES;

		LaserShadesCard() : Card(cardsData().get("LaserGlasses")) {};
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class BowCard : public Card {
public:
	constexpr static cardId_type id = _card_BOW;

	BowCard() : Card(cardsData().get("Bow")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class PulgaCard : public Card {
public:
	constexpr static cardId_type id = _card_PULGA;

	PulgaCard() : Card(cardsData().get("Tick")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult ,BattleScene* where );
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SpearCard : public Card {
public:
	constexpr static cardId_type id = _card_SPEAR;

	SpearCard() : Card(cardsData().get("Spear")) {};
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

	AssaultRifleCard() : Card(cardsData().get("AssaultRifle")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  LightRifleCard: public Card {
public:
	constexpr static cardId_type id = _card_LIGHTRIFLE;

	LightRifleCard() : Card(cardsData().get("LightBeam")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  MegaphoneCard : public Card {
public:
	constexpr static cardId_type id = _card_MEGAPHONE;

	MegaphoneCard() : Card(cardsData().get("Speaker")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  RiotShieldCard : public Card {
public:
	constexpr static cardId_type id = _card_RIOTSHIELD;

	RiotShieldCard() : Card(cardsData().get("RiotShield")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	void checkCollisionWithBullets(GameObject* shield, BattleScene* where);
};
class  CheatGunCard : public Card {
public:
	constexpr static cardId_type id = _card_CHEATGUN;

	CheatGunCard() : Card(cardsData().get("CheatGun")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class RitualAxeCard : public Card {
private:
	int enemiesKilled;
public:
	constexpr static cardId_type id = _card_RITUALAXE;

	RitualAxeCard() : Card(cardsData().get("RitualAxe")) { enemiesKilled = 0; };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	void enemieKilled();
};
class  LaserKatanaCard : public Card {
public:
	LaserKatanaCard() : Card(cardsData().get("Katana Laser")) {};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
