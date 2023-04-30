#include "ShopScene.h"
#include "../core/SDLApplication.h"

// Constructora
ShopScene::ShopScene() : NodeScene(), selectedCard(nullptr), buyButton(nullptr) {

	// Fondo
	background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	int rand = SDLApplication::instance()->getRandInt(0, 2);
	(rand == 0) ? background->addComponent<Image>(SDLApplication::getTexture("ShopSceneBackground1")) : 
		background->addComponent<Image>(SDLApplication::getTexture("ShopSceneBackground2"));

	// Dinero actual del PlayerData
	showMoney();

	// Boton de salida (esquina superior izquierda)
	Vector2D pos = Vector2D(1110 - IS_BUTTON_WIDTH / 2, 660);
	exitButton = addGameObject<Button>(_grp_UI, []() { SDLApplication::returnToMapScene(); }, pos, AnimatorInfo(EXIT));
	// Seleccion de cartas a mostrar en la tienda
	for (int i = 0; i < SHOP_NUMBER_OF_CARDS; i++) {
		rand = SDLApplication::instance()->getRandInt(0, maxCardId);
		for (int j = 0; j < i; j++) {
			if (rand == alreadyInStore[j]) {
				rand = SDLApplication::instance()->getRandInt(0, maxCardId);
				j = -1;
			}
		}
		alreadyInStore[i] = rand;

		myItems[i] = createItem(CardId(rand), 100, 200, i);
	}

	exitButton->setAsDefaultButton();
	myItems[0].card->setAsCurrentButton();
}

// Destructora
ShopScene::~ShopScene() {
}

void ShopScene::handleInput() {
	GameState::handleInput();
	if (gmCtrl_.goBack()) {
		if (exitButton->isCurrentButton()) {
			for (int i = 0; i < myItems.size() && exitButton->isCurrentButton(); ++i) {
				if (myItems[i].card != nullptr) myItems[i].card->setAsCurrentButton();
			}
		}
		else {
			exitButton->setAsCurrentButton();
		}
	}
}

// Deselecciona la carta
void ShopScene::deselectCard() {
	// Si hay carta seleccionada...
	if (selectedCard != nullptr) {
		// La coloca a su posicion normal
		selectedCard->card->getComponent<Transform>()->setY(SHOP_CARD_UNSELECTED_POSY);
		// Quita el precio y su marco
		selectedCard->priceObj->setAlive(false);
		selectedCard->priceFrame->setAlive(false);
		// Quita el boton de comprar
		hideBuyButton();
		// Se deselecciona
		selectedCard = nullptr;
	}
}

// Selecciona la carta
void ShopScene::selectCard() {
	// Selecciona la carta del lastButtonIndex
	selectedCard = &myItems[lastButtonIndex];
	
	// La coloca en su posicion de seleccionada y guarda el transform
	selectedCard->card->getComponent<Transform>()->setY(SHOP_CARD_SELECTED_POSY);
	Transform* selectedCardTransform = selectedCard->card->getComponent<Transform>();

	// Añade el marco trasero del dinero
	selectedCard->priceFrame = addGameObject();
	selectedCard->priceFrame->addComponent<Transform>(Vector2D(selectedCardTransform->getPos().getX(), selectedCardTransform->getPos().getY() + selectedCardTransform->getHeight() + 1), VECTOR_ZERO, selectedCardTransform->getWidth(), MM_BUTTON_HEIGHT);
	selectedCard->priceFrame->addComponent<Image>(SDLApplication::getTexture("MoneyFrame"));

	// Muestra su precio (se crea el objeto del precio (texto) debajo de la carta)
	selectedCard->priceObj = addGameObject();
	selectedCard->priceObj->addComponent<Transform>(Vector2D(selectedCardTransform->getPos().getX() + selectedCardTransform->getWidth() / 2 - USED_FONT_SIZE, selectedCardTransform->getPos().getY() + selectedCardTransform->getHeight() + 12), VECTOR_ZERO, SHOP_CARD_PRICE_WIDTH, SHOP_CARD_PRICE_HEIGHT);
	SDL_Color color;
	if (selectedCard->price < myMoney) color = COLOR_WHITE;
	else color = COLOR_RED;
	selectedCard->priceObj->addComponent<TextComponent>(SDLApplication::getFont(FONT_SS_REG22), to_string(selectedCard->price), color);
	
	// Muestra el boton de comprar
	buyButton = addGameObject<Button>(_grp_UI, buy(), SHOP_BUYBUTTON_POSITION, AnimatorInfo(BUY), lastButtonIndex, nullptr, 1.5f, 0.4f);
}

void ShopScene::buyCard() {
	// Si se puede comprar
	if (canBuy()) {
		#ifdef _DEBUG
		cout << "COMPRA" << endl;
		#endif
		// Le quita al dinero actual el precio de la carta
		myMoney -= selectedCard->price;
		PlayerData::instance()->setMoney(myMoney);
		// Lo anade al inventario
		moneyPrint->getComponent<TextComponent>()->changeText(to_string(myMoney));
		pD().addCardToLibrary(selectedCard->cardObj, 1);
		// Elimina la carta
		myItems[lastButtonIndex].card->setAlive(false);
		myItems[lastButtonIndex].cardObj = _card_NULL;
		myItems[lastButtonIndex].priceObj->setAlive(false);
		// Deselecciona
		deselectCard();
		myItems[lastButtonIndex].card = nullptr;
	}
	else {
		#ifdef _DEBUG
		cout << "NO SE PUEDE COMPRAR" << endl;
		#endif

		// Hacer aqui la animacion de que no se puede comprar

	}
}

void ShopScene::hideBuyButton() {
	if (buyButton != nullptr) buyButton->setAlive(false);
}

void ShopScene::showMoney() {
	// Marco del dinero actual (marco -first y moneda - second)
	moneyFrame.first = addGameObject();
	moneyFrame.second = addGameObject();
	moneyFrame.first->addComponent<Transform>(SHOP_MONEY_FRAME_POSITION, VECTOR_ZERO, SHOP_MONEY_FRAME_WIDTH, SHOP_MONEY_FRAME_HEIGHT, 0);
	moneyFrame.first->addComponent<Image>(SDLApplication::getTexture("MoneyFrame"));
	moneyFrame.second->addComponent<Transform>(SHOP_MONEY_COIN_POSITION, VECTOR_ZERO, COIN_WIDHT, COIN_HEIGHT, 0);
	moneyFrame.second->addComponent<Image>(SDLApplication::getTexture("Coin"));

	// Coge el dinero actual de PlayerDaya
	myMoney = pD().getMoney();

	// Lo muestra visualmente
	moneyPrint = addGameObject();
	moneyPrint->addComponent<Transform>(SHOP_MONEY_POSITION, VECTOR_ZERO, SHOP_MONEY_WIDTH, SHOP_MONEY_HEIGHT, 0);
	moneyPrint->addComponent<TextComponent>(SDLApplication::getFont(FONT_SS_REG30), to_string(myMoney), COLOR_WHITE);
}

void ShopScene::showExitButton() {
	if (exitButton != nullptr) exitButton->setAlive(false);
	exitButton = addGameObject<Button>(_grp_UI, []() { SDLApplication::returnToMapScene(); }, SHOP_BUYBUTTON_POSITION, AnimatorInfo(EXIT), lastButtonIndex);
	exitButton->setAsCurrentButton();
}

CallBack ShopScene::changeSelected() {
	return [&]() {
		// Se deselecciona y se selecciona (cambia de carta)
		deselectCard();
		selectCard();
		buyButton->setAsCurrentButton();
	};
}

CallBack ShopScene::buy() {
	return [&]() {
		buyCard();

		// Si no hay ninguna carta, sale el boton de salir
		if (isShopEmpty()) {
			hideBuyButton();
			showExitButton();
		}
	};
}

// Crea un item (crea el objeto de carta, lo anade al grupo de cartas
Item ShopScene::createItem(CardId cardType, int minPrice, int maxPrice, int i) {
	itemToInsert.cardObj = cardType;
	itemToInsert.card = addGameObject<Button>(_grp_CARDS, changeSelected(), Vector2D(SHOP_CARD_OFFSET_X + CARD_WIDTH * SHOP_NUMBER_OF_CARDS * i, SHOP_CARD_UNSELECTED_POSY), AnimatorInfo(Card::getCardIDfromEnum(cardType), UI_CARD_WIDTH, UI_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT, CARD_NUMROWS, CARD_NUMCOLS), i, nullptr, 0.5f, 0.5f);
	itemToInsert.price = SDLApplication::instance()->getRandInt(minPrice, maxPrice + 1);

	Transform* tr = itemToInsert.card->getComponent<Transform>();
	itemToInsert.ammo.first = addGameObject();
	itemToInsert.ammo.second = addGameObject();

	Vector2D decsPos = Vector2D(tr->getPos().getX() + 10, tr->getPos().getY() + 10);
	itemToInsert.ammo.first->addComponent<Transform>(decsPos, Vector2D(), UI_AMMO_NUMBERS_WIDTH, UI_AMMO_NUMBERS_HEIGHT);
	auto anim = itemToInsert.ammo.first->addComponent<Animator>(SDLApplication::getTexture(STATISTICS_NUMBERS), CARDS_NUMBERS_WIDTH, CARDS_NUMBERS_HEIGHT, CARDS_NUMBERS_ROWS, CARDS_NUMBERS_COLUMNS);
	for (int j = 0; j < N_NUMBERS - 2; j++) anim->createAnim(to_string(j), j, j, 1, 0);
	//anim->play(to_string(itemToInsert.cardObj / 10));

	return itemToInsert;
}

// Comprueba que haya una carta seleccionada y si se puede comprar con el dinero actual
bool ShopScene::canBuy() {
	return selectedCard != nullptr && myMoney >= selectedCard->price;
}

// Devuelve si la tienda esta vacia y pasa por referencia el indice debido
bool ShopScene::isShopEmpty() {
	int i = 0; bool empty = true;
	while (i < myItems.size() && empty) {
		if (myItems[i].cardObj != _card_NULL) {
			empty = false;
		}
		else ++i;
	}
	return empty;
}