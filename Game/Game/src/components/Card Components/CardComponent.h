#include <vector>
#include <algorithm>
#include <deque>
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../core/Vector2D.h"
#include "../../gameObjects/Card Objects/Card.h"
#include "../General Components/Animator.h"

#include "../../core/GameControl.h"

#pragma once
class BattleScene;
class CardCounter;
class CardComponent : public Component {
	private:
		Card* tutorialInitCard;
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
		bool locked = false, automatic = false, attacking = false, abiliting = false;
		bool tutorial, system;

		GameControl& gmCtrl_;

		void initDeck();
		void reshufflePile();
		void newHand();
		void drawCard();
		void discardCard(deque<Card*>::iterator discarded);
		void attack(Vector2D playerPos, Vector2D mousePos);
		void ability(Vector2D playerPos, Vector2D mousePos);
		void switchActive(bool left = false);


	public:
		static const int id = _CARDCOMPONENT;
		CardComponent(bool tutorial = false);
		virtual ~CardComponent();
		void initComponent();
		void update();
		void handleInput();
		void setCounter(CardCounter* _cc) { _myCounter = _cc; }
		
		void attack();
		void ability();
		void selectLeft();
		void selectRight();
		void switchActive(int number);

		//Getters
		inline int getDeckSize() const { return deck.size(); }
		inline int getPileSize() const { return pile.size(); }
		inline deque<Card*> getHand() { return hand; }
		inline int getMana() const { return mana; }
		inline void setAutomatic(bool value) { automatic = value; }
		inline void setLocked(bool value) { locked = value; }
		inline bool getAutomatic() const { return automatic; }
		inline bool isLocked() const { return locked; }
		void setInitialDeck();

		inline bool isAttacking() const { return attacking; }
		inline bool isAbiliting() const { return abiliting; }
};

