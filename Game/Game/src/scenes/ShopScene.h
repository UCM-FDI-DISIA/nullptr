#pragma once
#include "../components/General Components/TextComponent.h"
#include "../components/General Components/Transform.h"
#include "../gameObjects/UI/Button.h"
#include "NodeScene.h"
#include "../data/PlayerData.h"
#include <map>

const int SHOP_NUMBER_OF_CARDS = 4;

struct Item {
	Button* card;
	CardId cardObj;
	GameObject* priceObj;
	int price;
};

class ShopScene : public NodeScene {
private:
	GameObject* background;

	int myMoney;
	GameObject* moneyPrint;
	int alreadyInStore[SHOP_NUMBER_OF_CARDS];
	array<Item, SHOP_NUMBER_OF_CARDS> myItems;
	Item itemToInsert;
	Item* selectedCard;
	Button* buyButton;
	Button* exitButton;
public:
	// Constructora
	ShopScene();
	// Destructora
	virtual ~ShopScene();
	
	void hideBuyButton();
	void showMoney();
	void showExitButton();

	void deselectCard();
	void selectCard();

	void buyCard();

	CallBack changeSelected();
	
	CallBack buy();
	

	// Crea un item
	Item createItem(CardId cardType, int minPrice, int maxPrice, int i);
	// Comprueba que haya una carta seleccionada y si se puede comprar con el dinero actual
	bool canBuy();
	// Devuelve si la tienda esta vacia y pasa por referencia el indice debido
	bool isShopEmpty();
};