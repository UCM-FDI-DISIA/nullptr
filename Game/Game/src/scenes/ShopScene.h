#pragma once
#include "../components/General Components/TextComponent.h"
#include "../components/General Components/Transform.h"
#include "../gameObjects/UI/Button.h"
#include "NodeScene.h"
#include <map>

struct Item {
	Button* card;
	GameObject* priceObj;
	int price;
};

class ShopScene : public NodeScene {
private:
	GameObject* background;
	Item* selectedCard;
	Button* buyButton;
	Button* exitButton;
	int myMoney;
	int alreadyInStore[SHOP_NUMBER_OF_CARDS];
	map<int,Item> myItems;
	GameObject* moneyPrint;
public:
	// Constructora HAY QUE COGER EL DINERO DE PLAYERDATA
	ShopScene(int money);
	void showPrice();
	void hidePrice();
	void showBuyButton();
	void hideBuyButton();
	void showMoney();
	void hideMoney();
	void showExitButton();
	void hideExitButton();
	CallBack changeSelected();
	void change();
	void hideCard();
	CallBack buy();
	bool canBuy();
};