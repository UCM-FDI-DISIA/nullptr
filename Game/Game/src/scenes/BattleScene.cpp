#include "BattleScene.h"

// Constructora
BattleScene::BattleScene(int a) : GameState() {
	cout << "Has entrado en la escena de Batalla" << endl;
  
	// Quitar cuando se cree el mapa de combate
	floor = addGameObject();
	floor->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH*2, WIN_HEIGHT*2);
	floor->addComponent<Image>(SDLApplication::getTexture("FloorPast"));

	player = addGameObject<Player>();
	camera->startFollowObject(player);
	enemies.push_back(
		addGameObject<RangedEnemy>(Vector2D(0, 0), 50, player)
	);
	enemies.push_back(
		addGameObject<MeleeEnemy>(Vector2D(0, 0), 50, player)
	);
	Button* MainMenu = addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(BUTTON_FRAME_SPRITE_WIDTH + 10, BUTTON_SPRITE_HEIGHT + 10),
		EXIT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, BUTTON_WIDTH, BUTTON_HEIGHT);
	MainMenu->getComponent<Animator>()->attachToCamera();

	CardComponent* cardComp = player->getComponent<CardComponent>();
	addGameObject<CardCounter>(true, cardComp);
	addGameObject<CardCounter>(false, cardComp);

	hand = addGameObject<HandUI>(cardComp);
}

void BattleScene::mainMenu() {
	SDLApplication::newScene<MapScene>();
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

// Llamar a la creaci�n de la UI
void BattleScene::recreateUI() {
	hand->createUI();
}