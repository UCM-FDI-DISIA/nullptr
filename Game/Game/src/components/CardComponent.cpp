#include "CardComponent.h"
#include "../core/PlayerData.h"
#include "../sdlutils/InputHandler.h"
CardComponent::CardComponent() {
	deck = InputHandler::instance();
	initDeck();
	maxMana = mMana;
	mana = mMana;
	active = 0;
	attackMult = 0;
}

void CardComponent::attack(Vector2D playerPos, Vector2D mousePos) {
	if (downTime <= 0) {
		hand[active]->attack(playerPos, mousePos, attackMult);
		hand[active]->use();
		downTime = hand[active]->getDownTime() / cadenceMult;
		if (hand[active]->getUses() <= 0)discardCard(active);
	}
}

void CardComponent::ability(Vector2D playerPos, Vector2D mousePos) {
		if (hand[active]->getMana() <= mana) {
			hand[active]->ability(playerPos, mousePos, attackMult);
			discardCard(active);
		}
}


void CardComponent::switchActive(bool left) {
	if (left)
		--active;
	else
		++active;
	active %= 4;
}

void CardComponent::initDeck() {
	srand(time(0));
	random_shuffle(deck.begin(), deck.end());
	newHand();
}

void CardComponent::reshufflePile() {
	//Semilla aleatoria, con tiempo del ordenador
	srand(time(0));
	//Copia y mezcla
	pile.swap(deck);
	random_shuffle(deck.begin(), deck.end());
}

void CardComponent::newHand() {
	handSize = 4;
	//Si la mano esta vacia se barajan nuevas cartas
	if (deck.size() == 0)
		reshufflePile();
	for (int i = 0; i++; i < 4) {
		drawCard(i);
		//Si se vacia la mano al ir sacando cartas
		if (deck.size() == 0)
			reshufflePile();
	}
}

void CardComponent::drawCard(int handPos) {
	hand[handPos] = deck.back();
	deck.pop_back();
}

void CardComponent::discardCard(int discarded) {
	pile.push_back(hand[discarded]);
	hand[discarded]->resetUses();
	hand[discarded] = nullptr;
	handSize--;
	if (handSize <= 0) {
		newHand();
	}
}

