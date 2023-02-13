#include <vector>
#include <array>
#include <algorithm>
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

		int mana, maxMana;

		void initDeck();
		void reshufflePile();
		void newHand();
		void drawCard(int handPos);
		void discardCard(int discarded);


	public:
		static const int id = _CARDCOMPONENT;
		CardComponent(vector<Card*> wholeDeck, int maxMana);
		void attack(Vector2D playerPos, Vector2D mousePos);
		void ability(Vector2D playerPos, Vector2D mousePos);
		void switchActive(bool left = false);
		void initComponent();
		void update();
		void handleInput();
		void render();
};

