#pragma once
#include "../components/General Components/TextComponent.h"
#include "../components/General Components/Transform.h"
#include "../gameObjects/UI/Button.h"
#include "NodeScene.h"

struct Item {
	Button* card;
	GameObject* price;
};

class ShopScene : public NodeScene {
private:
	Item* selectedCard;
	Button* buyButton;
	int myMoney;
	int alreadyInStore[SHOP_NUMBER_OF_CARDS];
	Item myItems[SHOP_NUMBER_OF_CARDS];
	GameObject* moneyPrint;

public:
	// Constructora HAY QUE COGER EL DINERO DE PLAYERDATA
	ShopScene(int money);
	void showPrice();
	void hidePrice();
	void showBuyButton();
	void hideBuyButton();
	CallBack changeSelected();
	static void buy();
};