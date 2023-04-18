#pragma once
#include "GameState.h"
#include <map>
#include <vector>


class Card;
struct InventoryInfo {

	int cuantity = 0;
	int cuantityDeck = 0;
	CardId card;
	GameObject* myText;

	InventoryInfo() : cuantity(0), cuantityDeck(0), card(_card_NULL) { };
};
struct InventoryCard
{
	GameObject* deckButton;
	GameObject* deckImage;
	GameObject* deckText;
};

class InventoryScene : public GameState {
private:
	std::map<string,InventoryInfo> inventory;
	std::map<CardId, InventoryCard> deckButtons;
	vector<int> stats;
public:
	InventoryScene();
	virtual ~InventoryScene();
	void createSymbol(Vector2D _pos, string key, string text, int val);
	void createPanels();
	void createMoneyInfo();
	void createObjects();
	void createCards();
	void createDeckCards(CardId crd, int column);
	void createCard(Vector2D pos, CardId card, bool deck);
};