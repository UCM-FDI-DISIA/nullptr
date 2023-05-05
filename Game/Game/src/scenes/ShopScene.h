#pragma once
#include "../components/General Components/TextComponent.h"
#include "../components/General Components/Transform.h"
#include "../gameObjects/UI/Button.h"
#include "GameState.h"
#include "../data/PlayerData.h"
#include <map>

struct Item {
	Button* card;
	CardId cardObj;
	GameObject* priceObj;
	GameObject* priceFrame;
	pair<GameObject*, GameObject*> ammo;
	pair<GameObject*, GameObject*> mana;
	int price;
};

class ShopScene : public GameState {
private:
	GameObject* background;
	Music* shopMusic;

	SoundEffect* buySound;
	SoundEffect* cantBuySound;

	int myMoney;
	GameObject* moneyPrint;
	pair<GameObject*, GameObject*> moneyFrame;

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
	void handleInput() override;
	
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

	// Crea los números de munición y maná de las cartas
	void createNumber(GameObject* number, Vector2D pos, int value, char type);
};