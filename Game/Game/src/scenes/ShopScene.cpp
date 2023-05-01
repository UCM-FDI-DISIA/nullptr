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
		// Mueve los números
		Transform* tr = selectedCard->ammo.first->getComponent<Transform>(); tr->setY(tr->getY() + 50);
		tr = selectedCard->ammo.second->getComponent<Transform>(); tr->setY(tr->getY() + 50);
		tr = selectedCard->mana.first->getComponent<Transform>(); tr->setY(tr->getY() + 50);
		tr = selectedCard->mana.second->getComponent<Transform>(); tr->setY(tr->getY() + 50);
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

	// Mueve los números
	Transform* tr = selectedCard->ammo.first->getComponent<Transform>(); tr->setY(tr->getY() - 50);
	tr = selectedCard->ammo.second->getComponent<Transform>(); tr->setY(tr->getY() - 50);
	tr = selectedCard->mana.first->getComponent<Transform>(); tr->setY(tr->getY() - 50);
	tr = selectedCard->mana.second->getComponent<Transform>(); tr->setY(tr->getY() - 50);

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
		myItems[lastButtonIndex].ammo.first->setAlive(false);
		myItems[lastButtonIndex].ammo.second->setAlive(false);
		myItems[lastButtonIndex].mana.first->setAlive(false);
		myItems[lastButtonIndex].mana.second->setAlive(false);
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

// Crea un item (crea el objeto de carta, lo anade al grupo de cartas)
Item ShopScene::createItem(CardId cardType, int minPrice, int maxPrice, int i) {
	itemToInsert.cardObj = cardType;
	itemToInsert.card = addGameObject<Button>(_grp_CARDS, changeSelected(), Vector2D(SHOP_CARD_OFFSET_X + CARD_WIDTH * SHOP_NUMBER_OF_CARDS * i, SHOP_CARD_UNSELECTED_POSY), AnimatorInfo(Card::getCardIDfromEnum(cardType), UI_CARD_WIDTH, UI_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT, CARD_NUMROWS, CARD_NUMCOLS), i, nullptr, 0.5f, 0.5f);
	itemToInsert.price = SDLApplication::instance()->getRandInt(minPrice, maxPrice + 1);

	// Guardar transform y obtener datos de la carta
	Transform* tr = itemToInsert.card->getComponent<Transform>();
	CardData card = cardsData().get(Card::getCardIDfromEnum(cardType));

	// Añadir número
	itemToInsert.ammo.first = addGameObject(_grp_UI);
	itemToInsert.ammo.second = addGameObject(_grp_UI);
	itemToInsert.mana.first = addGameObject(_grp_UI);
	itemToInsert.mana.second = addGameObject(_grp_UI);

	// Crear números
	Vector2D decsPos = Vector2D(tr->getPos().getX() + 15, tr->getPos().getY() + 18);
	createNumber(itemToInsert.ammo.first, decsPos, card.maxUses / 10, 'a');
	createNumber(itemToInsert.ammo.second, decsPos + Vector2D(11, 0), card.maxUses % 10, 'a');
	createNumber(itemToInsert.mana.first, decsPos + Vector2D(3, 40), card.mana / 10, 'm');
	createNumber(itemToInsert.mana.second, decsPos + Vector2D(14, 40), card.mana % 10, 'm');

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

// Crear un número según los datos recibidos
void ShopScene::createNumber(GameObject* number, Vector2D pos, int value, char type) {
	// Añadir componentes (transform y animator)
	number->addComponent<Transform>(pos, Vector2D(), UI_AMMO_NUMBERS_WIDTH, UI_AMMO_NUMBERS_HEIGHT);
	
	// Seleccionar textura
	Texture* txt;
	if (type == 'a') txt = SDLApplication::getTexture(STATISTICS_NUMBERS);
	else txt = SDLApplication::getTexture(CARDS_NUMBERS);

	// Añadir animator y crear animaciones
	auto anim = number->addComponent<Animator>(txt, CARDS_NUMBERS_WIDTH, CARDS_NUMBERS_HEIGHT, CARDS_NUMBERS_ROWS, CARDS_NUMBERS_COLUMNS);
	for (int j = 0; j < N_NUMBERS - 2; j++) anim->createAnim(to_string(j), j, j, 1, 0);

	// Reproducir animación correspondiente
	anim->play(to_string(value));
}