#include "CardComponent.h"
#include "../core/PlayerData.h"
#include "../core/GameObject.h"
#include "../scenes/BattleScene.h"
#include "../sdlutils/InputHandler.h"

CardComponent::CardComponent() {
	maxMana = PlayerData::instance()->getMaxMana();
	mana = PlayerData::instance()->getMaxMana();
	attackMult = PlayerData::instance()->getAttackMult();
	fireRateMult = PlayerData::instance()->getFireRateMult();
	deck = PlayerData::instance()->getDeck();
	initDeck();
}

void CardComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
	where = dynamic_cast<BattleScene*>(gStt);
}

void CardComponent::update() {
	if (downTime > 0) {
		downTime -= 0.1;
	}
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
		(*active)->attack(playerPos, mousePos, attackMult, where);
		(*active)->use();
		downTime = (*active)->getDownTime() / fireRateMult;
		if ((*active)->getUses() <= 0)discardCard(active);
	}
}

void CardComponent::ability(Vector2D playerPos, Vector2D mousePos) {
		if ((*active)->getMana() <= mana) {
			(*active)->ability(playerPos, mousePos, attackMult, where);
			mana -= (*active)->getMana();
			discardCard(active);
		}
}


void CardComponent::switchActive(bool left) {
	if (left)
		--active;
	else
		++active;
}

void CardComponent::switchActive(int number) {
	if (number >= 0 && number < hand.size()) {
		active = hand.begin();
		std::advance(active, number);
	}
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
	cout << "Se barajo la pila de descartes para formar un nuevo mazo";
}

void CardComponent::newHand() {
	//Si la mano esta vacia se barajan nuevas cartas
	if (deck.size() == 0)
		reshufflePile();
	for (int i = 0; i < 4; i++) {
		drawCard();
		//Si se vacia la mano al ir sacando cartas
		if (deck.size() == 0)
			reshufflePile();
	}
	active = hand.begin();
}

void CardComponent::drawCard() {
	hand.push_back(deck.back());
	deck.pop_back();
}

void CardComponent::discardCard(deque<Card*>::iterator discarded) {
	pile.push_back(*discarded);
	(*discarded)->resetUses();
	active = hand.erase(discarded);
	if(active != hand.begin())
		--active;
	if (hand.size() <= 0) {
		cout << "Se acabo tu mano\n";
		newHand();
	}
}


