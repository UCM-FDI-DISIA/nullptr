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

	addGameObject<CardCounter>(game, true, player->getComponent<CardComponent>());
	addGameObject<CardCounter>(game, false, player->getComponent<CardComponent>());
}

void BattleScene::mainMenu(SDLApplication* _game) {
	SDLApplication::newScene<MapScene>(_game);
}

vector<GameObject*>& BattleScene::getEnemies() {
	return enemies;
}

void BattleScene::OnPlayerDies() {
	GameObject* message = addGameObject<GameObject>();
	message->addComponent<Transform>(Vector2D(MESSAGE_X, MESSAGE_Y), Vector2D(0,0), MESSAGE_W, MESSAGE_H);
	message->addComponent<Image>(SDLApplication::instance()->getTexture("YouDied"));

	GameObject* marco = addGameObject();
	marco->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 103, WIN_HEIGHT* 2 / 3 - 44), Vector2D(0, 0), 190, 90);
	marco->addComponent<Animator>(SDLApplication::instance()->getTexture("Marco"),
		BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);

	addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT / 2),
		EXIT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marco);
}