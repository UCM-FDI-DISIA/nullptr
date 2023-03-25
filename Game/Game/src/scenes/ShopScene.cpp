#include "ShopScene.h"
#include "../core/SDLApplication.h"

ShopScene::ShopScene(int money) : NodeScene(), myMoney(money), selectedCard(nullptr), buyButton(nullptr) {

	cout << "Has entrado en la escena de Tienda" << endl;

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


		myItems[i].card = addGameObject<Button>(_grp_CARDS, changeSelected(), Vector2D(SHOP_CARD_OFFSET_X + CARD_WIDTH * SHOP_NUMBER_OF_CARDS * i, SHOP_CARD_UNSELECTED_POSY), AnimatorInfo(Card::getCardIDfromEnum(rand), UI_CARD_WIDTH, UI_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT), i);

		/*moneyPrint = addGameObject();
		moneyPrint->addComponent<Transform>(Vector2D(WIN_WIDTH - 200, 30), VECTOR_ZERO, 100, 50, 0);
		moneyPrint->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL24"),to_string(myMoney) ,color);*/
	}

	addGameObject<Button>(_grp_UI, [](){ SDLApplication::returnToMapScene(); }, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), AnimatorInfo(EXIT));
}

void ShopScene::showPrice() {
	selectedCard->price = addGameObject();
	Transform* selectedCardTransform = selectedCard->card->getComponent<Transform>();
	selectedCard->price->addComponent<Transform>(Vector2D(selectedCardTransform->getPos().getX() + selectedCardTransform->getWidth() / 2 - USED_FONT_SIZE, selectedCardTransform->getPos().getY() + selectedCardTransform->getHeight()), VECTOR_ZERO, SHOP_CARD_PRICE_WIDTH, SHOP_CARD_PRICE_HEIGHT);
	// En el rand() debe ir el precio de la carta seleccionada
	selectedCard->price->addComponent<TextComponent>(&sdlutils().fonts().at(USED_FONT), to_string(sdlutils().rand().nextInt(100, 201)), COLOR_WHITE);
}

void ShopScene::hidePrice() {
	selectedCard->price->setAlive(false);
}

void ShopScene::showBuyButton() {
	buyButton = addGameObject<Button>(_grp_UI, buy, SHOP_BUYBUTTON_POSITION, AnimatorInfo(BUY));
}

void ShopScene::hideBuyButton() {
	buyButton->setAlive(false);
}

CallBack ShopScene::changeSelected() {

	return [&]() {
		if (selectedCard != nullptr) {
			selectedCard->card->getComponent<Transform>()->setY(SHOP_CARD_UNSELECTED_POSY);
			hidePrice();
		}

		selectedCard = &myItems[lastButtonIndex];
		selectedCard->card->getComponent<Transform>()->setY(SHOP_CARD_SELECTED_POSY);
		showPrice();
		showBuyButton();
	};
}

void ShopScene::buy() {
	cout << "COMPRA" << endl;

	// Aqui se debe gestionar:
	// - Bajar el dinero actual del Player
	// - A�adir carta
}