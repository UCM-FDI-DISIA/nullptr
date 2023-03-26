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

	createPanels();

	int numD = 0;
	for (int i = 0; i < info.size(); i++) {
		if (info[i].cuantityDeck > 0) { addGameObject<InventoryCard>(this, &info[i], i, numD); numD++; }
		else addGameObject<InventoryCard>(this, &info[i], i);
	}

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

void InventoryScene::createPanels() {
	GameObject* dp = addGameObject();
	dp->addComponent<Transform>(DP_POSITION, VECTOR_ZERO, DP_WIDTH, DP_HEIGHT);
	dp->addComponent<Image>(&sdlutils().images().at(DECK_PANEL));

	GameObject* op = addGameObject();
	op->addComponent<Transform>(OP_POSITION, VECTOR_ZERO, OP_WIDTH, OP_HEIGHT);
	op->addComponent<Image>(&sdlutils().images().at(OBJECTS_PANEL));

	GameObject* ip = addGameObject();
	ip->addComponent<Transform>(IP_POSITION, VECTOR_ZERO, IP_WIDTH, IP_HEIGHT);
	ip->addComponent<Image>(&sdlutils().images().at(INVENTORY_PANEL));

	GameObject* sp = addGameObject();
	sp->addComponent<Transform>(SP_POSITION, VECTOR_ZERO, SP_WIDTH, SP_HEIGHT);
	sp->addComponent<Image>(&sdlutils().images().at(STATS_PANEL));

}