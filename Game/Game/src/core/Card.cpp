#include "../cards/Cards.h"

Card Card::getCard(CardId type) {
	switch (type)
	{
	case gun:
		return Gun();
	case sword:
		return Sword();
	case laserShades:
		return LaserShades();
	default:
		break;
	}
}