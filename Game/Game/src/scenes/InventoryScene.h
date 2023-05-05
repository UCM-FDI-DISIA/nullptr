#pragma once
#include "GameState.h"
#include <map>
#include <vector>
#include "../components/General Components/TextComponent.h"
#include "../components/General Components/PopupComponent.h"

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
	GameObject* deckTextFrame;
	pair<GameObject*, GameObject*> ammo;
	pair<GameObject*, GameObject*> mana;
};

class InventoryScene : public GameState {
private:
	string texts[3] = {
		"BIENVENIDO A TU INVENTARIO. Aquí podrás ver todas las cartas que posees y las que tienes en el mazo, así como tus objetos y estadísticas.",
		"También podrás modificar tu mazo añadiendo cartas del inventario (clicando sobre ellas en la zona de inventario) ",
		"o retirando las ya presentes(clicando sobre ellas en la zona de inventario)",
	};
	
	bool interactive;
	std::map<string, InventoryInfo> inventory;
	std::map<CardId, InventoryCard> deckButtons;
	vector<int> stats;

	GameObject* inventoryPanel;
	GameObject* deckPanel;

	GameObject* screen;
	GameObject* tuto;
	GameObject* text1;
	GameObject* text2;
	Button* button;

	Button* exitButton;

	int cardsInDeck;
	int camYLimit;
	Transform* camTr;

public:
	InventoryScene();
	virtual ~InventoryScene();

	virtual void update();

	void handleInput() override;
	void createSymbol(Vector2D _pos, string key, string text, int val);
	void createPanels();
	GameObject* createPanel(Vector2D pos, int w, int h, string textureKey);
	void createMoneyInfo();
	void createObjects();
	void createCards();
	void createDeckCards(CardId crd, int column, int row);
	Button* createCard(Vector2D pos, CardId card, bool deck);
	void reloadDeckCards();

	void createNumber(GameObject* number, Vector2D pos, int value, char type);

	void activatePopUp();
	void deactivatePopUp();
};