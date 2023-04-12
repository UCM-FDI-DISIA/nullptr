#include "InventoryScene.h"
#include "../core/SDLApplication.h"



InventoryScene::InventoryScene() : GameState() {
	
	vector<CardId> currentLibrary = PlayerData::instance()->getLibrary();
	vector<Card*> currentDeck = PlayerData::instance()->getDeck();

	for (int i = 0; i < currentLibrary.size();i++) {

		if (!inventory.count(Card::getCardIDfromEnum(currentLibrary[i]))) {
			inventory[Card::getCardIDfromEnum(currentLibrary[i])].card = currentLibrary[i];
		}
		inventory[Card::getCardIDfromEnum(currentLibrary[i])].cuantity++;
	}

	for (int j = 0; j < currentDeck.size(); j++) {
		inventory[Card::getCardIDfromEnum(currentLibrary[j])].cuantityDeck++;
	}

	// Llamamos a Player data para pillar la info de las cartas que se tienen
	stats.push_back(PlayerData::instance()->getMaxHP());
	stats.push_back(PlayerData::instance()->getMaxMana());
	stats.push_back(PlayerData::instance()->getPlayerMoveSpeed() / 2);
	stats.push_back(PlayerData::instance()->getAttackMult() * 100);
	stats.push_back(PlayerData::instance()->getFireRateMult() * 100);

	//Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
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
	createButton(IS_EXIT_BUTTON_POS, IS_EXITFRAME_BUTTON_POS, []() { SDLApplication::popGameState(); }, EXIT);
}

// Crear un bot�n especificado en la escena
void InventoryScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key, IS_BUTTON_WIDTH, IS_BUTTON_HEIGHT);
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), IS_BUTTONFRAME_WIDTH, IS_BUTTONFRAME_HEIGHT);
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols);

	// Crear bot�n
	addGameObject<Button>(_cb, _bPos, aI, frame);
}

void InventoryScene::createSymbol(Vector2D _pos, string key, string text, int val) {
	GameObject* symbol = addGameObject();

	symbol->addComponent<Transform>(_pos, VECTOR_ZERO, SYMBOL_DIMENSIONS, SYMBOL_DIMENSIONS);
	symbol->addComponent<Image>(SDLApplication::getTexture(key));

	GameObject* stat = addGameObject();
	stat->addComponent<Transform>(_pos + STAT_OFFSET, VECTOR_ZERO, 100, 24);
	stat->addComponent<TextComponent>(SDLApplication::getFont("ARIAL24"), text);

	GameObject* value = addGameObject();
	value->addComponent<Transform>(_pos + STAT_VALUE_OFFSET, VECTOR_ZERO, 50, 24);
	value->addComponent<TextComponent>(SDLApplication::getFont("ARIAL24"), to_string(val));
}

void InventoryScene::createPanels() {
	GameObject* dp = addGameObject();
	dp->addComponent<Transform>(DP_POSITION, VECTOR_ZERO, DP_WIDTH, DP_HEIGHT);
	dp->addComponent<Image>(SDLApplication::getTexture(DECK_PANEL));

	GameObject* op = addGameObject();
	op->addComponent<Transform>(OP_POSITION, VECTOR_ZERO, OP_WIDTH, OP_HEIGHT);
	op->addComponent<Image>(SDLApplication::getTexture(OBJECTS_PANEL));

	GameObject* ip = addGameObject();
	ip->addComponent<Transform>(IP_POSITION, VECTOR_ZERO, IP_WIDTH, IP_HEIGHT);
	ip->addComponent<Image>(SDLApplication::getTexture(INVENTORY_PANEL));

	GameObject* sp = addGameObject();
	sp->addComponent<Transform>(SP_POSITION, VECTOR_ZERO, SP_WIDTH, SP_HEIGHT);
	sp->addComponent<Image>(SDLApplication::getTexture(STATS_PANEL));

}

void InventoryScene::createMoneyInfo() {
	//Icono de moneda
	GameObject* coin = addGameObject();
	coin->addComponent<Transform>(COIN_OFFSET, Vector2D(), 64, 64);
	coin->addComponent<Image>(SDLApplication::getTexture("Coin"));

	// Texto
	GameObject* text = addGameObject();
	text->addComponent<Transform>(MONEY_TEXT, VECTOR_ZERO, 70, 48);
	text->addComponent<TextComponent>(SDLApplication::getFont("ARIAL48"), "Dinero");

	// Texto con el numero de monedas
	GameObject* mon = addGameObject();
	mon->addComponent<Transform>(MONEY_VALUE, VECTOR_ZERO, 50, 48);
	int m = PlayerData::instance()->getMoney();
	mon->addComponent<TextComponent>(SDLApplication::getFont("ARIAL48"), to_string(m));
}

void InventoryScene::createObjects() {
	auto objs = PlayerData::instance()->getRelics();

	for (int i = 0; i < objs.size(); i++) {
		GameObject* g = addGameObject();
		g->addComponent<Transform>(OBJECTS_POSITIONS[i], VECTOR_ZERO, OBJECTS_DIMENSIONS, OBJECTS_DIMENSIONS);
		g->addComponent<Image>(objs[i]->texture);
	}
}

void InventoryScene::createCards() {
	bool row = false;
	int column = 0;
	for (map<string, InventoryInfo>::iterator it = inventory.begin(); it != inventory.end(); it++) {

		Vector2D pos = Vector2D(20 + 160 * column, 50 + 220 * (row ? 0 : 1));
		createCard(pos, it->second.card);
		
		Vector2D posD = Vector2D(20 + 160 * column, DECK_HEIGHT);
			createCard(posD, it->second.card);
		if (row) {
			column++;
		}
		row = !row;
		

	}
}

void InventoryScene::createCard(Vector2D pos, CardId card) {
	GameObject* cardObj = addGameObject();
	cardObj->addComponent<Transform>(pos, VECTOR_ZERO, CARD_WIDTH*2, CARD_HEIGHT*2);
	cardObj->addComponent<Image>(cardsData().get(Card::getCardIDfromEnum(card)).texture);

	/*Button* b = addGameObject<Button>([&, cD = myData, f = found]() { if (f && !selected) selectCard(cD); }, pos, AnimatorInfo("CardSelection", ALB_CARD_W, ALB_CARD_H, myData.texture->width(), myData.texture->height(), 1, 4));
	Animator* a = b->getComponent<Animator>();
	a->createAnim(ONOUT, UNSELECTED_CARD_ANIM);
	a->createAnim(ONOVER, SELECTED_CARD_ANIM);
	a->createAnim(ONCLICK, CLICKED_CARD_ANIM);
	a->play(ONOUT);*/
}

InventoryScene::~InventoryScene() {
	vector<Card*> newDeck;
	for (map<string, InventoryInfo>::iterator it = inventory.begin(); it != inventory.end(); it++) {
		for (int i = 0; i < it->second.cuantityDeck; i++) {
			newDeck.push_back(Card::getCard(it->second.card));
		}
	}
	PlayerData::instance()->setDeck(newDeck);
}