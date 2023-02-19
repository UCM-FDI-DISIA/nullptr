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
	Button* MainMenu = addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50),
		PLAY, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	MainMenu->getComponent<Animator>()->attachToCamera();

	addGameObject<CardCounter>(true, player->getComponent<CardComponent>());
	addGameObject<CardCounter>(false, player->getComponent<CardComponent>());
}

void BattleScene::mainMenu() {
	SDLApplication::newScene<MapScene>();
}

vector<GameObject*>& BattleScene::getEnemies() {
	return enemies;
}