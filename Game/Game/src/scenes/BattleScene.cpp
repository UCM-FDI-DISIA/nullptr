#include "BattleScene.h"

// Constructora
BattleScene::BattleScene(SDLApplication* _game,int a) : GameState(_game) {
	cout << "Has entrado en la escena de Batalla" << endl;
  
	// Quitar cuando se cree el mapa de combate
	floor = addGameObject();
	floor->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	floor->addComponent<Image>(_game->getTexture("Player"));

	player = addGameObject<Player>(game);
	camera->startFollowObject(player);

	Button* MainMenu = addGameObject<Button>(mainMenu, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50),
		PLAY, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	stateScene.push_back(MainMenu);

	/*GameObject* deck = new GameObject();
	deck->addComponent<Transform>(Vector2D(REVERSE_WIDTH / 4, WIN_HEIGHT - ( 6 * REVERSE_HEIGHT / 5)), Vector2D(0, 0), REVERSE_WIDTH, REVERSE_HEIGHT);
	deck->addComponent<Image>(game->getTexture("Reverse"));
	stateScene.push_back(deck);

	GameObject* discards = new GameObject();
	discards->addComponent<Transform>(Vector2D(WIN_WIDTH - (5 * REVERSE_WIDTH / 4), WIN_HEIGHT - (6 * REVERSE_HEIGHT / 5)), Vector2D(0, 0), REVERSE_WIDTH, REVERSE_HEIGHT);
	discards->addComponent<Image>(game->getTexture("Reverse"));
	stateScene.push_back(discards);*/

	GameObject* mazo = new CardCounter(_game, true, player->getComponent<CardComponent>());
	stateScene.push_back(mazo);
	MainMenu->getComponent<Animator>()->attachToCamera();
}

void BattleScene::mainMenu(SDLApplication* _game) {
	SDLApplication::newScene<MapScene>(_game);
}

vector<GameObject*>& BattleScene::getEnemies() {
	return enemies;
}