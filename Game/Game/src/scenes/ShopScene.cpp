#include "ShopScene.h"
#include "../core/SDLApplication.h"

ShopScene::ShopScene(int money) : NodeScene(), myMoney(money), selectedCard(nullptr), buyButton(nullptr) {

	cout << "Has entrado en la escena de Tienda" << endl;

	background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("ShopSceneBackground"));

	for (int i = 0; i < SHOP_NUMBER_OF_CARDS; i++) {
		int rand = sdlutils().rand().nextInt(0, SHOP_NUMBER_OF_CARDS + 1);
		for (int j = 0; j < i; j++)
		{
			if (rand == alreadyInStore[j]) {
				rand = sdlutils().rand().nextInt(0, SHOP_NUMBER_OF_CARDS + 1);
				j = -1;
			}
		}
		alreadyInStore[i] = rand;

		Item itemToInsert;
		itemToInsert.card = addGameObject<Button>(_grp_CARDS, changeSelected(), Vector2D(SHOP_CARD_OFFSET_X + CARD_WIDTH * SHOP_NUMBER_OF_CARDS * i, SHOP_CARD_UNSELECTED_POSY), AnimatorInfo(Card::getCardIDfromEnum(rand), UI_CARD_WIDTH, UI_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT), i);
		// Cambiar el rand() por un precio elegido
		itemToInsert.price = sdlutils().rand().nextInt(100, 201);
		
		myItems[i] = itemToInsert;
	}
	exitButton = addGameObject<Button>(_grp_UI, []() { SDLApplication::returnToMapScene(); }, SHOP_EXITBUTTON_POSITION, AnimatorInfo(EXIT));

	showMoney();
}

void ShopScene::showPrice() {
	selectedCard->priceObj = addGameObject();
	Transform* selectedCardTransform = selectedCard->card->getComponent<Transform>();
	selectedCard->priceObj->addComponent<Transform>(Vector2D(selectedCardTransform->getPos().getX() + selectedCardTransform->getWidth() / 2 - USED_FONT_SIZE, selectedCardTransform->getPos().getY() + selectedCardTransform->getHeight()), VECTOR_ZERO, SHOP_CARD_PRICE_WIDTH, SHOP_CARD_PRICE_HEIGHT);
	if (selectedCard->price < myMoney) selectedCard->priceObj->addComponent<TextComponent>(&sdlutils().fonts().at(USED_FONT), to_string(selectedCard->price), COLOR_WHITE);
	else selectedCard->priceObj->addComponent<TextComponent>(&sdlutils().fonts().at(USED_FONT), to_string(selectedCard->price), COLOR_RED);
}

void ShopScene::hidePrice() {
	selectedCard->priceObj->setAlive(false);
}

void ShopScene::showBuyButton() {
	if (buyButton != nullptr) hideBuyButton();
	buyButton = addGameObject<Button>(_grp_UI, buy(), SHOP_BUYBUTTON_POSITION, AnimatorInfo(BUY), lastButtonIndex);
}

void ShopScene::hideBuyButton() {
	buyButton->setAlive(false);
}

void ShopScene::showMoney() {
	moneyPrint = addGameObject();
	moneyPrint->addComponent<Transform>(SHOP_MONEY_POSITION, VECTOR_ZERO, SHOP_MONEY_WIDTH, SHOP_MONEY_HEIGHT, 0);
	moneyPrint->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL24"), to_string(myMoney), COLOR_WHITE);
}

void ShopScene::hideMoney() {
	moneyPrint->setAlive(false);
}

void ShopScene::showExitButton() {
	if (buyButton != nullptr) hideBuyButton();
	if (exitButton != nullptr) hideExitButton();
	exitButton = addGameObject<Button>(_grp_UI, []() { SDLApplication::returnToMapScene(); }, SHOP_BUYBUTTON_POSITION, AnimatorInfo(EXIT), lastButtonIndex);
}

void ShopScene::hideExitButton() {
	exitButton->setAlive(false);
}

CallBack ShopScene::changeSelected() {
	return [&]() {
		if (selectedCard != nullptr) {
			selectedCard->card->getComponent<Transform>()->setY(SHOP_CARD_UNSELECTED_POSY);
			hidePrice();
		}
		change();
	};
}

void ShopScene::change() {
	selectedCard = &myItems[lastButtonIndex];
	selectedCard->card->getComponent<Transform>()->setY(SHOP_CARD_SELECTED_POSY);
	showPrice();
	showBuyButton();
}

void ShopScene::hideCard() {
	myItems[lastButtonIndex].card->setAlive(false);
	myItems[lastButtonIndex].priceObj->setAlive(false);
	myItems.erase(lastButtonIndex);
	if (!myItems.empty()) {
		lastButtonIndex = myItems.begin()->first;
		change();
	}
	else showExitButton();
}

CallBack ShopScene::buy() {

	// Aqui se debe gestionar:
	// - Bajar el dinero actual del Player
	// - A�adir carta
	
	return [&]() {
		if (canBuy()) {
			cout << "COMPRA" << endl;
			myMoney -= selectedCard->price;
			moneyPrint->getComponent<TextComponent>()->changeText(to_string(myMoney));
			hideCard();
		}
		else cout << "NO SE PUEDE COMPRAR" << endl;
	};
}

bool ShopScene::canBuy() {
	return myMoney >= selectedCard->price;
}