#include "../core/Vector2D.h"
#include "../sdlutils/Texture.h"

#pragma once

enum CardId
{
	gun = 0,
	sword,
	laserShades,
};
class BattleScene;
class Card
{
	protected:
		int damage, maxUses, remainingUses, mana;
		float downtime;
		std::string name, abilityText, attackText;
		Texture* texture;

	public:
		Card() {};
		static Card getCard(CardId type);
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {}
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {}
		int getUses() { return remainingUses; }
		void use() { remainingUses -= 1;}
		void resetUses() { remainingUses = maxUses;}
		int getMana() { return mana; }
		int getDownTime() { return downtime; }

};

