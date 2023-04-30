#pragma once
#include "GameState.h"
#include <map>
#include <vector>
#include "../components/General Components/TextComponent.h"


class Card;
struct InventoryInfo {

	int cuantity = 0;
	int cuantityDeck = 0;
	CardId card;
	TextComponent* myText;
	TextComponent* myDeckText;

	InventoryInfo() : cuantity(0), cuantityDeck(0), card(_card_NULL), myText(nullptr), myDeckText(nullptr) { };
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

	Button* exitButton;
public:
	InventoryScene();
	virtual ~InventoryScene();
	void handleInput() override;
	void createSymbol(Vector2D _pos, string key, string text, int val);
	void createPanels();
	void createPanel(Vector2D pos, int w, int h, string textureKey);
	void createMoneyInfo();
	void createObjects();
	void createCards();
	void createDeckCards(CardId crd, int column);
	Button* createCard(Vector2D pos, CardId card, bool deck);
	void reloadDeckCards();
};