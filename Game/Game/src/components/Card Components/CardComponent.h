#include <vector>
#include <array>
#include <algorithm>
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../core/Vector2D.h"
#include "../../gameObjects/Card Objects/Card.h"
#include <deque>
#include "../General Components/Animator.h"

#pragma once
class BatleScene;
class CardCounter;
class CardComponent : public Component {
	private:
		BattleScene* where;
		vector<Card*> deck;
		deque<Card*> hand;
		vector<Card*> pile;
		Transform* tr;
		deque<Card*>::iterator active;
		GameObject *card;
		CardCounter* _myCounter;
		float downTime, attackMult, fireRateMult;

		int mana, maxMana;
		bool locked = false, automatic = false;

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
		void setCounter(CardCounter* _cc) { _myCounter = _cc; }
		
		//Getters
		int getDeckSize() { return deck.size(); }
		int getPileSize() { return pile.size(); }
		deque<Card*> getHand() { return hand; }
		int getMana() { return mana; }
		void setAutomatic(bool value) { automatic = value; }
		void setLocked(bool value) { locked = value; }
};

