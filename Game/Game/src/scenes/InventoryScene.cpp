#include "InventoryScene.h"
#include "../core/SDLApplication.h"

InventoryScene::InventoryScene() : GameState() {
	// Llamamos a Player data para pillar la info de las cartas que se tienen
	info = PlayerData::instance()->getInventoryInfo();
	cr = PlayerData::instance()->getReceivedCards();

	//Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("InventoryBackground"));

	createDeck();
	createLibrary();
	//Icono de moneda
	GameObject* coin = addGameObject();
	coin->addComponent<Transform>(COIN_OFFSET, Vector2D(), 32, 32);
	coin->addComponent<Image>(SDLApplication::getTexture("Coin"));

	// Los simbolos
	for (int i = 0; i < 5; i++) {
		createSymbol(SYMBOL_POSITIONS[i], SYMBOLS_KEYS[i]);
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

void InventoryScene::createSymbol(Vector2D _pos, string key) {
	GameObject* symbol = addGameObject();

	symbol->addComponent<Transform>(_pos, VECTOR_ZERO, SYMBOL_DIMENSIONS, SYMBOL_DIMENSIONS);
	symbol->addComponent<Image>(&sdlutils().images().at(key));
}

void InventoryScene::createDeck() {
	int numD = 0;
	int i = 0;

	while (numD < 6 && i < info.size()) {
		if (info[i].cuantityDeck != 0) {
			GameObject* card = addGameObject();
			card->addComponent<Transform>(DECK_POSITIONS[numD], VECTOR_ZERO, CARD_WIDTH * 2, CARD_HEIGHT * 2);
			card->addComponent<Image>(info[i].card->texture);
			deck.push_back(card);
			numD++;
		}
		i++;
	}
}

void InventoryScene::deleteDeck() {
	for (GameObject* g : deck) {
		g->setAlive(false);
	}
	deck.clear();
}

void InventoryScene::createLibrary() {
	int numL = 0;
	
	for (int i = 0; i < info.size(); i++) {
		if (info[i].cuantityDeck == 0) {
			// Aqui se crearia la carta en su posicion determinada
		}
	}
}