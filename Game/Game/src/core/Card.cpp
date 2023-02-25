#include "../cards/Cards.h"

Card::Card(int _damage, int _maxUses, int _mana, float _downtime, float _bulletSpeed, std::string _data, Texture* _texture) :
	damage(_damage), maxUses(_maxUses), remainingUses(_maxUses), mana(_mana), downtime(_downtime), bulletSpeed(_bulletSpeed), texture(_texture) {
	//Procesamiento de _data con formato: "name$attackText&abilityText"
	int tS = 0;
	for (int i = 0; i < _data.length(); i++) {
		if (_data[i] == '$')
			tS++; 
		else {
			switch (tS) {
			case 0:
				name += _data[i];
				break;
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

//Devuelve la carta correspondiente al id
Card Card::getCard(CardId type) {

	// cleon says: podéis sacar un elemento random de un vector, y el elemento que sea una lambda
	switch (type)
	{
	case gun:
		return GunCard();
	case sword:
		return SwordCard();
	case laserShades:
		return LaserShadesCard();
	default:
		break;
	}
}