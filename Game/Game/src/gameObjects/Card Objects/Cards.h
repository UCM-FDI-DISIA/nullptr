#include "../Card Objects/Card.h"
#include "../../scenes/BattleScene.h"
#include "../../data/CardsDataContainer.h"
#include "../../scenes/GameState.h"
#pragma once

class GunCard : public Card {
	public:
		constexpr static cardId_type id = _card_GUN;

		GunCard() : Card(cardsData().get("Gun")) { attackSound = &sdlutils().soundEffects().at(SHOT_SOUND); };
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SwordCard : public Card {
	public:
		constexpr static cardId_type id = _card_SWORD;

		SwordCard() : Card(cardsData().get("Sword")) { attackSound = &sdlutils().soundEffects().at(SLASH_SOUND); };
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class TorchCard : public Card {
public:
	constexpr static cardId_type id = _card_TORCH;

	TorchCard() : Card(cardsData().get("Torch")) { attackSound = &sdlutils().soundEffects().at(SLASH_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class LaserShadesCard : public Card {
	public:
		constexpr static cardId_type id = _card_LASERGLASSES;

		LaserShadesCard() : Card(cardsData().get("LaserGlasses")) { attackSound = &sdlutils().soundEffects().at(SHOT_SOUND); };
		void spawnRay(Vector2D playerPos, Vector2D dir, float rotation, float attackMult, BattleScene* where, float speed, Vector2D offset);
		void spawnParallelRays(Vector2D playerPos, Vector2D dir, float rotation, float attackMult, BattleScene* where, float speed);
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class BowCard : public Card {
public:
	constexpr static cardId_type id = _card_BOW;

	BowCard() : Card(cardsData().get("Bow")) { attackSound = &sdlutils().soundEffects().at(SHOT_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class PulgaCard : public Card {
public:
	constexpr static cardId_type id = _card_PULGA;

	PulgaCard() : Card(cardsData().get("Tick")) { attackSound = &sdlutils().soundEffects().at(SHOT_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult ,BattleScene* where );
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SpearCard : public Card {
public:
	constexpr static cardId_type id = _card_SPEAR;

	SpearCard() : Card(cardsData().get("Spear")) { attackSound = &sdlutils().soundEffects().at(SLASH_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};

class SMGCard : public Card {
public:
	constexpr static cardId_type id = _card_SMG;

	SMGCard() : Card(cardsData().get("SMG")) { attackSound = &sdlutils().soundEffects().at(SHOT_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  AssaultRifleCard : public Card {
public:
	constexpr static cardId_type id = _card_ASSAULTRIFLE;

	AssaultRifleCard() : Card(cardsData().get("AssaultRifle")) { attackSound = &sdlutils().soundEffects().at(SHOT_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  LightRifleCard: public Card {
public:
	constexpr static cardId_type id = _card_LIGHTRIFLE;

	LightRifleCard() : Card(cardsData().get("LightBeam")) { attackSound = &sdlutils().soundEffects().at(SHOT_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  MegaphoneCard : public Card {
public:
	constexpr static cardId_type id = _card_MEGAPHONE;

	MegaphoneCard() : Card(cardsData().get("Speaker")) { attackSound = &sdlutils().soundEffects().at(SHOT_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class  RiotShieldCard : public Card {
public:
	constexpr static cardId_type id = _card_RIOTSHIELD;

	RiotShieldCard() : Card(cardsData().get("RiotShield")) { attackSound = &sdlutils().soundEffects().at(SLASH_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	void checkCollisionWithBullets(GameObject* shield, BattleScene* where);
};
class  CheatGunCard : public Card {
public:
	constexpr static cardId_type id = _card_CHEATGUN;

	CheatGunCard() : Card(cardsData().get("CheatGun")) { attackSound = &sdlutils().soundEffects().at(SHOT_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
class RitualAxeCard : public Card {
private:
	int enemiesKilled;
public:
	constexpr static cardId_type id = _card_RITUALAXE;

	RitualAxeCard() : Card(cardsData().get("RitualAxe")) { enemiesKilled = 0; attackSound = &sdlutils().soundEffects().at(SLASH_SOUND);
	};
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	void enemieKilled();
};
class  LaserKatanaCard : public Card {
public:
	LaserKatanaCard() : Card(cardsData().get("LaserKatana")) { attackSound = &sdlutils().soundEffects().at(SLASH_SOUND); };
	virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
	virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
};
