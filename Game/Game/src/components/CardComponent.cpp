#include "CardComponent.h"

void CardComponent::ability(Vector2D playerPos, Vector2D mousePos) {
	if (hand[active]->getMana() >= mana) {
		hand[active]->ability(playerPos, mousePos);
		discardCard(active);
	}
}

void CardComponent::attack(Vector2D playerPos, Vector2D mousePos) {
	hand[active]->attack(playerPos, mousePos);
	hand[active]->use();
	if (hand[active]->getUses() <= 0)discardCard(active);
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
	hand[discarded] = nullptr;
	pile.push_back(hand[discarded]);
	handSize--;
	if (handSize <= 0) {
		newHand();
	}
}

