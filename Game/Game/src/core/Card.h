#include "../core/Vector2D.h"
#include "../sdlutils/Texture.h"
#pragma once

class Card
{
	protected:
		int damage, maxUses, remainingUses, mana;
		float downtime;
		string name, abilityText, attackText;
		Texture* texture;

	public:
		Card() {}
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult) {}
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult) {}
		int getUses() { return remainingUses; }
		void use() { remainingUses -= 1;}
		void resetUses() { remainingUses = maxUses;}
		int getMana() { return mana; }
		int getDownTime() { return downtime; }
};

