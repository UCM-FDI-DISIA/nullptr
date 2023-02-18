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
		float downtime, bulletSpeed;
		std::string name, abilityText, attackText;
		Texture* texture;

	public:
		Card(int _damage, int _maxUses, int _mana, float _downtime, float _bulletSpeed, std::string _name, std::string _attackText, std::string _abilityText, Texture* _texture) :
			damage(_damage),maxUses(_maxUses),remainingUses(_maxUses),mana(_mana),downtime(_downtime),bulletSpeed(_bulletSpeed),
			name(_name), attackText(_attackText), abilityText(_abilityText), texture(_texture) {};
		static Card getCard(CardId type);
		virtual void attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		virtual void ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where);
		int getUses() { return remainingUses; }
		void use() { remainingUses -= 1;}
		void resetUses() { remainingUses = maxUses;}
		int getMana() { return mana; }
		int getDownTime() { return downtime; }

};

