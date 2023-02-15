#include "CardComponent.h"
#include "../core/PlayerData.h"
#include "../core/GameObject.h"
#include "../sdlutils/InputHandler.h"

CardComponent::CardComponent() {
	deck = PlayerData::instance()->getDeck();
	initDeck();
	maxMana = PlayerData::instance()->getMaxMana();
	mana = PlayerData::instance()->getMaxMana();
	attackMult = PlayerData::instance()->getAttackMult();
	fireRateMult = PlayerData::instance()->getFireRateMult();
	active = 0;
}

void CardComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
}

void CardComponent::handleInput() {
	if (InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { attack(tr->getPos(), InputHandler::instance()->getMousePos()); }
	if (InputHandler::instance()->getMouseButtonState(InputHandler::RIGHT)) { ability(tr->getPos(), InputHandler::instance()->getMousePos()); }
	if (InputHandler::instance()->mouseWheelDown()) { switchActive(false); }
	if (InputHandler::instance()->mouseWheelUp()) { switchActive(true); }
	if (InputHandler::instance()->isKeyJustDown(SDLK_1)) { switchActive(0); }
	if (InputHandler::instance()->isKeyJustDown(SDLK_2)) { switchActive(1); }
	if (InputHandler::instance()->isKeyJustDown(SDLK_3)) { switchActive(2); }
	if (InputHandler::instance()->isKeyJustDown(SDLK_4)) { switchActive(3); }
}


void CardComponent::attack(Vector2D playerPos, Vector2D mousePos) {
	if (downTime <= 0) {
		hand[active]->attack(playerPos, mousePos, attackMult);
		hand[active]->use();
		downTime = hand[active]->getDownTime() / fireRateMult;
		if (hand[active]->getUses() <= 0)discardCard(active);
	}
}

void CardComponent::ability(Vector2D playerPos, Vector2D mousePos) {
		if (hand[active]->getMana() <= mana) {
			hand[active]->ability(playerPos, mousePos, attackMult);
			mana -= hand[active]->getMana();
			discardCard(active);
		}
}


void CardComponent::switchActive(bool left) {
	if (left)
		--active;
	else
		++active;
	active %= hand.size();
}

void CardComponent::switchActive(int number) {
	if (number >= 0 && number < hand.size())
		active = number;
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
		drawCard();
		//Si se vacia la mano al ir sacando cartas
		if (deck.size() == 0)
			reshufflePile();
	}
}

void CardComponent::drawCard() {
	hand.push_back(deck.back());
	deck.pop_back();
}

void CardComponent::discardCard(int discarded) {
	pile.push_back(hand[discarded]);
	hand[discarded]->resetUses();
	hand[discarded] = nullptr;
	if (hand.size() <= 0) {
		newHand();
	}
}


