#include "BattleScene.h"

// Constructora
BattleScene::BattleScene(SDLApplication* _game,int a) : GameState(_game) {
	cout << "Has entrado en la escena de Batalla" << endl;
  
	// Quitar cuando se cree el mapa de combate
	floor = addGameObject();
	floor->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	floor->addComponent<Image>(_game->getTexture("Floor"));

	player = addGameObject<Player>(game);
	camera->startFollowObject(player);

	Button* MainMenu = addGameObject<Button>(mainMenu, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50),
		PLAY, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	MainMenu->getComponent<Animator>()->attachToCamera();

	CardComponent* cardComp = player->getComponent<CardComponent>();
	addGameObject<CardCounter>(game, true, cardComp);
	addGameObject<CardCounter>(game, false, cardComp);

	// Mano de la UI
	hand = addGameObject<HandUI>(game, cardComp);
}

void BattleScene::mainMenu(SDLApplication* _game) {
	SDLApplication::newScene<MapScene>(_game);
}

vector<GameObject*>& BattleScene::getEnemies() {
	return enemies;
}

// CAMBIOS DE UI
// Lamar a cambiar la carta seleccionada de la UI
void BattleScene::changeUISelected(bool key, int number) {
	hand->changeSelected(key, number);
}

// Llamar a borrar una carta de la UI
void BattleScene::discardUI(deque<Card*>::iterator discarded) {
	hand->discard(discarded);
}

// Llamar a la creación de la UI
void BattleScene::recreateUI() {
	hand->createUI();
}