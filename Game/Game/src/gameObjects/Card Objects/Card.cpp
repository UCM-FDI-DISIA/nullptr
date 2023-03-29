#include "../Card Objects/Cards.h"

Card::Card(int _damage, int _maxUses, int _mana, float _downtime, std::string _data, Texture* _texture) :
	damage(_damage), maxUses(_maxUses), remainingUses(_maxUses), mana(_mana), downtime(_downtime), texture(_texture) {
	//Procesamiento de _data con formato: "name$attackText$abilityText"
	int tS = 0;
	for (int i = 0; i < _data.length(); i++) {
		if (_data[i] == '$')
			tS++; 
		else {
			switch (tS) {
			case 0:
				name += _data[i];
				break;
				std::cout << name;
			case 1:
				attackText += _data[i];
				break;
			case 2:
				abilityText += _data[i];
				break;
				default:
					break;
			}
		}
		
	}
};
Card::Card(CardData myData) : 
	damage(myData.damage), maxUses(myData.maxUses), remainingUses(myData.maxUses), mana(myData.mana), downtime(myData.downTime),
	name(myData.name), attackText(myData.attackText), abilityText(myData.abilityText), texture(myData.texture){}

Card::~Card() {}

//Devuelve la carta correspondiente al id
Card Card::getCard(CardId type) {

	// cleon says: pod�is sacar un elemento random de un vector, y el elemento que sea una lambda
	switch (type)
	{
	case _card_GUN: return GunCard();
	case _card_SWORD: return SwordCard();
	case _card_TORCH: return TorchCard();
	case _card_LASERGLASSES: return LaserShadesCard();
	case _card_BOW: return BowCard();
	case _card_PULGA: return PulgaCard();
	case _card_SPEAR: return SpearCard();
	case _card_SMG: return SMGCard();
	case _card_ASSAULTRIFLE: return AssaultRifleCard();
	case _card_LIGHTRIFLE: return LightRifleCard();
	case _card_MEGAPHONE: return MegaphoneCard();
	case _card_RIOTSHIELD: return RiotShieldCard();
	case _card_RITUALAXE: return RitualAxeCard();
	case _card_CHEATGUN: return CheatGunCard();
	default: break;
	}
}
