#include <vector>
#include <array>
#include "Component.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "../data/Card.h"

#pragma once
class CardComponent : public Component {
	private:
		vector<Card*> deck;
		array<Card*, 4> hand;
		vector<Card*> pile;
		Card* active;

		int mana, maxMana;

		void initDeck();
		void resuflePile();
		void drawCard();
		void discardCard(Card* discarded);


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

