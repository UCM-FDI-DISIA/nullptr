#include <vector>
#include <array>
#include <algorithm>
#include "Component.h"
#include "Transform.h"
#include "../core/Vector2D.h"
#include "../core/Card.h"
#include <deque>

#pragma once
class CardComponent : public Component {
	private:
		vector<Card*> deck;
		deque<Card*> hand;
		vector<Card*> pile;
		Transform* tr;
		deque<Card*>::iterator active;
		float downTime, attackMult, fireRateMult;

		int mana, maxMana;

		void initDeck();
		void reshufflePile();
		void newHand();
		void drawCard();
		void discardCard(deque<Card*>::iterator discarded);
		void attack(Vector2D playerPos, Vector2D mousePos);
		void ability(Vector2D playerPos, Vector2D mousePos);
		void switchActive(bool left = false);
		void switchActive(int number);


	public:
		static const int id = _CARDCOMPONENT;
		CardComponent();
		void initComponent();
		void update();
		void handleInput();
		
};

