#include <vector>
#include <array>
#include "Component.h"
#include "Transform.h"
#include "../core/Vector2D.h"
#include "../data/Card.h"

#pragma once
class CardComponent : public Component {
	private:
		vector<Card*> deck;
		array<Card*, 4> hand;
		vector<Card*> pile;
		int active,handSize;
		float downTime, attackMult, cadenceMult;

		int mana, maxMana;

		void initDeck();
		void resuflePile();
		void newHand();
		void drawCard();
		void discardCard(int discarded);


	public:
		static const int id = _CARDCOMPONENT;
		void attack(Vector2D playerPos, Vector2D mousePos);
		void ability(Vector2D playerPos, Vector2D mousePos);
		void switchActive(bool left = false);
		void initComponent();
		void update();
		void handdleImput();
		void render();
};

