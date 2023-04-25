#include "InventoryScene.h"
#include "../core/SDLApplication.h"


// Se encarga de cargar todos los datos desde el dataplayer, así como obtener los datos del deck y de la library
InventoryScene::InventoryScene() : GameState() {
	
	vector<CardId> currentLibrary = PlayerData::instance()->getLibrary();
	vector<CardId> currentDeck = PlayerData::instance()->getDeckIds();

	for (int i = 0; i < currentLibrary.size();i++) {

		if (!inventory.count(Card::getCardIDfromEnum(currentLibrary[i]))) {
			inventory[Card::getCardIDfromEnum(currentLibrary[i])].card = currentLibrary[i];
		}
		inventory[Card::getCardIDfromEnum(currentLibrary[i])].cuantity++;
	}

	for (int j = 0; j < currentDeck.size(); j++) {
		inventory[Card::getCardIDfromEnum(currentDeck[j])].cuantityDeck++;
	}

	// Llamamos a Player data para pillar la info de las cartas que se tienen
	stats.push_back(PlayerData::instance()->getMaxHP());
	stats.push_back(PlayerData::instance()->getMaxMana());
	stats.push_back(PlayerData::instance()->getPlayerMoveSpeed() / 2);
	stats.push_back(PlayerData::instance()->getAttackMult() * 100);
	stats.push_back(PlayerData::instance()->getFireRateMult() * 100);

	//Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), Constant::getInt("WIN_WIDTH"), Constant::getInt("WIN_HEIGHT"));
	background->addComponent<Image>(SDLApplication::getTexture("InventoryBackground"));

	createPanels();
	createMoneyInfo();
	createObjects(); 
	createCards();

	
	// Los simbolos
	for (int i = 0; i < 5; i++) {
		createSymbol(SYMBOL_POSITIONS[i], SYMBOLS_KEYS[i], STATS_TEXTS[i], stats[i]);
	}
	// Creamos el boton de salir
	createButton(Constant::getVector2D("IS_EXIT_BUTTON_POS"), Constant::getVector2D("IS_EXITFRAME_BUTTON_POS"), [&]() {
		int cardsInDeck = 0;
	for (map<string, InventoryInfo>::iterator it = inventory.begin(); it != inventory.end(); it++) 
		if (inventory[Card::getCardIDfromEnum(it->second.card)].cuantityDeck > 0) cardsInDeck+= inventory[Card::getCardIDfromEnum(it->second.card)].cuantityDeck;
		if(cardsInDeck>=4)SDLApplication::popGameState(); 
		}, Constant::getString("EXIT"));
}

// Crear un bot�n especificado en la escena
void InventoryScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key, Constant::getInt("IS_BUTTON_WIDTH"), Constant::getInt("IS_BUTTON_HEIGHT"));
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), Constant::getInt("IS_BUTTONFRAME_WIDTH"), Constant::getInt("IS_BUTTONFRAME_HEIGHT"));
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), Constant::getInt("BUTTON_FRAME_SPRITE_WIDTH"), Constant::getInt("BUTTON_FRAME_SPRITE_HEIGHT"), aI.rows, aI.cols);

	// Crear bot�n
	addGameObject<Button>(_cb, _bPos, aI, frame);
}
void InventoryScene::createSymbol(Vector2D _pos, string key, string text, int val) {
	GameObject* symbol = addGameObject();

	symbol->addComponent<Transform>(_pos, Vector2D(), Constant::getInt("SYMBOL_DIMENSIONS"), Constant::getInt("SYMBOL_DIMENSIONS"));
	symbol->addComponent<Image>(SDLApplication::getTexture(key));

	GameObject* stat = addGameObject();
	stat->addComponent<Transform>(_pos + Constant::getVector2D("STAT_OFFSET"), Vector2D(), 100, 24);
	stat->addComponent<TextComponent>(SDLApplication::getFont("ARIAL24"), text);

	GameObject* value = addGameObject();
	value->addComponent<Transform>(_pos + Constant::getVector2D("STAT_VALUE_OFFSET"), Vector2D(), 50, 24);
	value->addComponent<TextComponent>(SDLApplication::getFont("ARIAL24"), to_string(val));
}
// Crea los paneles en los que se colocan las cartas
void InventoryScene::createPanels() {
	GameObject* dp = addGameObject();
	dp->addComponent<Transform>(Constant::getVector2D("DP_POSITION"), Vector2D(), Constant::getInt("DP_WIDTH"), Constant::getInt("DP_HEIGHT"));
	dp->addComponent<Image>(SDLApplication::getTexture(Constant::getString("DECK_PANEL")));

	GameObject* op = addGameObject();
	op->addComponent<Transform>(Constant::getVector2D("OP_POSITION"), Vector2D(), Constant::getInt("OP_WIDTH"), Constant::getInt("OP_HEIGHT"));
	op->addComponent<Image>(SDLApplication::getTexture(Constant::getString("OBJECTS_PANEL")));

	GameObject* ip = addGameObject();
	ip->addComponent<Transform>(Constant::getVector2D("IP_POSITION"), Vector2D(), Constant::getInt("IP_WIDTH"), Constant::getInt("IP_HEIGHT"));
	ip->addComponent<Image>(SDLApplication::getTexture(Constant::getString("INVENTORY_PANEL")));

	GameObject* sp = addGameObject();
	sp->addComponent<Transform>(Constant::getVector2D("SP_POSITION"), Vector2D(), Constant::getInt("SP_WIDTH"), Constant::getInt("SP_HEIGHT"));
	sp->addComponent<Image>(SDLApplication::getTexture(Constant::getString("STATS_PANEL")));

}

void InventoryScene::createMoneyInfo() {
	//Icono de moneda
	GameObject* coin = addGameObject();
	coin->addComponent<Transform>(Constant::getVector2D("COIN_OFFSET"), Vector2D(), 64, 64);
	coin->addComponent<Image>(SDLApplication::getTexture("Coin"));

	// Texto
	GameObject* text = addGameObject();
	text->addComponent<Transform>(Constant::getVector2D("MONEY_TEXT"), Vector2D(), 70, 48);
	text->addComponent<TextComponent>(SDLApplication::getFont("ARIAL48"), "Dinero");

	// Texto con el numero de monedas
	GameObject* mon = addGameObject();
	mon->addComponent<Transform>(Constant::getVector2D("MONEY_VALUE"), Vector2D(), 50, 48);
	int m = PlayerData::instance()->getMoney();
	mon->addComponent<TextComponent>(SDLApplication::getFont("ARIAL48"), to_string(m));
}

void InventoryScene::createObjects() {
	auto objs = PlayerData::instance()->getRelics();

	for (int i = 0; i < objs.size(); i++) {
		GameObject* g = addGameObject();
		g->addComponent<Transform>(OBJECTS_POSITIONS[i], Vector2D(), Constant::getInt("OBJECTS_DIMENSIONS"), Constant::getInt("OBJECTS_DIMENSIONS"));
		g->addComponent<Image>(objs[i]->texture);
	}
}
// Se encarga de crear las imagenes de las cartas en el inventario con sus cantidades
void InventoryScene::createCards() {
	bool row = false;
	int column = 0;
	int deckColumn = 0;
	for (map<string, InventoryInfo>::iterator it = inventory.begin(); it != inventory.end(); it++) {

		Vector2D pos = Vector2D(20 + 160 * column, 50 + 220 * (row ? 0 : 1));
		string temp = Card::getCardIDfromEnum(it->second.card);
		createCard(pos, it->second.card, false);
		
		if (it->second.cuantityDeck > 0)createDeckCards(it->second.card, deckColumn);
			row = !row;
			deckColumn++;
		if (row) {
			column++;
		}
		

	}
}
// Se encarga de crear las imagenes de las cartas en la zona del deck
void InventoryScene::createDeckCards(CardId crd, int column)
{
	Vector2D posD = Vector2D(20 + 160 * column, Constant::getInt("DECK_HEIGHT"));
	createCard(posD, crd, true);
}
// Se encarga de crear el objeto de la carta, así como sus botones y le añaden la funcionalidad para quitar o poner en el deck
void InventoryScene::createCard(Vector2D pos, CardId crd, bool dck) {
	// Imagen de la carta
	GameObject* cardObj = addGameObject();
	cardObj->addComponent<Transform>(pos, Vector2D(), Constant::getInt("CARD_WIDTH") * 2, Constant::getInt("CARD_HEIGHT") * 2);
	cardObj->addComponent<Image>(cardsData().get(Card::getCardIDfromEnum(crd)).texture);
	// Botón de la carta con su función 
	Button* b = addGameObject<Button>([&, deck = dck, card = crd, myPos = pos]()
		{

			// Dependiendo si esta en el deck o no, realiza la función de sumar o restar la carta del deck
			if (deck? inventory[Card::getCardIDfromEnum(card)].cuantityDeck > 0 :inventory[Card::getCardIDfromEnum(card)].cuantityDeck < inventory[Card::getCardIDfromEnum(card)].cuantity) {
				if (deck) {
					inventory[Card::getCardIDfromEnum(card)].cuantityDeck--;
					if (inventory[Card::getCardIDfromEnum(card)].cuantityDeck == 0) {
						deckButtons[card].deckButton->setAlive(false);
						deckButtons[card].deckImage->setAlive(false);
						deckButtons[card].deckText->setAlive(false);
					}
				}
				// Si estaba en el deck y su cantidad cae a 0, se borra la imagen y su boton para que se represente que no hay este carta en el deck
				else {
					inventory[Card::getCardIDfromEnum(card)].cuantityDeck++;
					if (inventory[Card::getCardIDfromEnum(card)].cuantityDeck == 1) {
						for (auto obj : deckButtons)
						{
							obj.second.deckButton->setAlive(false);
							obj.second.deckImage->setAlive(false);
							obj.second.deckText->setAlive(false);
						}
						int column = 0;
						for (map<string, InventoryInfo>::iterator it = inventory.begin(); it != inventory.end(); it++)
						{
							if (it->second.cuantityDeck > 0)
							{
								createDeckCards(it->second.card, column);
								column++;
							}

						}
					}
				}
				inventory[Card::getCardIDfromEnum(card)].myText->getComponent<TextComponent>()->changeText(to_string(inventory[Card::getCardIDfromEnum(card)].cuantityDeck)
					+ "/" + to_string(inventory[Card::getCardIDfromEnum(card)].cuantity));
			}
		}
		, pos, AnimatorInfo("CardSelection", Constant::getInt("ALB_CARD_W"), Constant::getInt("ALB_CARD_H"),
		cardsData().get(Card::getCardIDfromEnum(crd)).texture->width(), cardsData().get(Card::getCardIDfromEnum(crd)).texture->height(), 1, 4));
	// Texto que indica cuantas cartas hay en el deck
	GameObject* text = addGameObject();
	inventory[Card::getCardIDfromEnum(crd)].myText = text;
	text->addComponent<Transform>(Vector2D (pos.getX()+ Constant::getInt("CARD_WIDTH") * 2, pos.getY()), Vector2D(), 70, 48);
	text->addComponent<TextComponent>(SDLApplication::getFont("ARIAL16"),  to_string(inventory[Card::getCardIDfromEnum(crd)].cuantityDeck) + "/" + to_string(inventory[Card::getCardIDfromEnum(crd)].cuantity));
	if (dck) {
		deckButtons[crd].deckButton = b;
		deckButtons[crd].deckImage = cardObj;
		deckButtons[crd].deckText = text;
	}
}

InventoryScene::~InventoryScene() {
	vector<Card*> newDeck;
	vector<CardId> newDeckId;
	for (map<string, InventoryInfo>::iterator it = inventory.begin(); it != inventory.end(); it++) {
		for (int i = 0; i < it->second.cuantityDeck; i++) {
			newDeck.push_back(Card::getCard(it->second.card));
			newDeckId.push_back(it->second.card);
		}
	}
	PlayerData::instance()->setDeck(newDeck);
	PlayerData::instance()->setDeckId(newDeckId);
}