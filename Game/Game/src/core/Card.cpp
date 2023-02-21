#include "../cards/Cards.h"

//Devuelve la carta correspondiente al id
Card Card::getCard(CardId type) {
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