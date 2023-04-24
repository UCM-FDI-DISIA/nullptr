#pragma once
#include "../../core/Vector2D.h"
#include "../../sdlutils/Texture.h"
#include "../../data/CardsDataContainer.h"

class BattleScene;
class Card {
	protected:
		int damage, maxUses, remainingUses, mana;
		float downtime;
		std::string name, abilityText, attackText;
		Texture* texture;
	public:
		Card(int _damage, int _maxUses, int _mana, float _downtime, std::string _data, Texture* _texture);
		Card(CardData myData);
		virtual ~Card();
		static Card* getCard(CardId type);
		//Ataque
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {}
		//Habilidad
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {}
		//Se gasta un uso
		void use() { remainingUses -= 1;}
		//Se reinician sus usos respecto a los m�ximos
		void resetCard() { remainingUses = maxUses;}
		

		// Getters
		int getDamage() { return damage; }
		int getMaxUses() { return maxUses; }
		int getUses() { return remainingUses; }
		int getMana() { return mana; }
		float getDownTime() { return downtime; }
		string getName() { return name; }
		string getAbilityText() { return abilityText; }
		string getAttackText() { return attackText; }
		Texture* getTexture() { return texture; }

		static std::string getCardIDfromEnum(int type) {
			switch (type) {
			case _card_GUN: return "Gun";
			case _card_SWORD: return "Sword";
			case _card_TORCH: return "Torch";
			case _card_LASERGLASSES: return "LaserGlasses";
			case _card_BOW: return "Bow";
			case _card_PULGA: return "Tick";
			case _card_SPEAR: return "Spear";
			case _card_SMG: return "SMG";
			case _card_ASSAULTRIFLE: return "AssaultRifle";
			case _card_LIGHTRIFLE: return "LightBeam";
			case _card_MEGAPHONE: return "Speaker";
			case _card_RIOTSHIELD: return "RiotShield";
			case _card_CHEATGUN: return "CheatGun";
			case _card_RITUALAXE: return "RitualAxe";
			default: return REVERSE;
			}
		}
};

