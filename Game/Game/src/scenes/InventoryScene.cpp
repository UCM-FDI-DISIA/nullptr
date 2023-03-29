#include "InventoryScene.h"
#include "../core/SDLApplication.h"

InventoryScene::InventoryScene() : GameState(), deck(vector<int>(6, -1)) {
	// Llamamos a Player data para pillar la info de las cartas que se tienen
	info = PlayerData::instance()->getInventoryInfo();
	cr = PlayerData::instance()->getReceivedCards();
	deckCards = 0;

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

	int numD = 0;
	for (int i = 0; i < info.size(); i++) {
		if (info[i].cuantityDeck > 0) { addGameObject<InventoryCard>(this, &info[i], i, numD); deck[i] = numD; numD++; deckCards += info[i].cuantityDeck; }
		else addGameObject<InventoryCard>(this, &info[i], i);
	}
	
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

void InventoryScene::removeFromDeck(int ind) {
	deck[ind] = -1;
}

int InventoryScene::getFirstDeckPos() {
	int i = 0;
	bool found = false;
	while (!found && i < deck.size()) {
		if (deck[i] == -1) found = true;
		else i++;
	}

	if (found) { deck[i] = i; return i; }
}

void InventoryScene::changeDeckCardsNumber(int num) {
	deckCards += num;
}