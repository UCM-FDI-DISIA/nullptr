#include "CardComponent.h"

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

}

void CardComponent::initDeck() {

}

void CardComponent::resuflePile() {

}

void CardComponent::newHand() {

}

void CardComponent::drawCard() {

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

