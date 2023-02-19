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
	
	GameObject* en = addGameObject<RangedEnemy>(Vector2D(0, 0), 50, player);
	enemies.push_back(en);
	en = addGameObject<MeleeEnemy>(Vector2D(0, 0), 50, player);
	enemies.push_back(en);

	deck = addGameObject<CardCounter>(true, player->getComponent<CardComponent>());
	pile = addGameObject<CardCounter>(false, player->getComponent<CardComponent>());
}

void BattleScene::mainMenu() {
	SDLApplication::newScene<MainMenuScene>();
}

vector<GameObject*>& BattleScene::getEnemies() {
	return enemies;
}

void BattleScene::OnPlayerDies() {
	////Desactivo los enemigos y mis contadores de cartas
	//for (auto it = enemies.begin(); it != enemies.end(); it++) {
	//	(*it)->setAlive(false);
	//}
	//enemies.clear();
	//pile->setAlive(false);
	//deck->setAlive(false);

	////Fijo el suelo a la camara
	//floor->getComponent<Image>()->attachToCamera();
	////Creo el objeto con la imagen del mensaje de muerte
	//GameObject* message = addGameObject();
	//message->addComponent<Transform>(Vector2D(MESSAGE_X, MESSAGE_Y), Vector2D(0,0), MESSAGE_W, MESSAGE_H);
	//auto im = message->addComponent<Image>(SDLApplication::getTexture("YouDied"));
	//im->attachToCamera();
	////Creo el boton y su marco y los fijo a la camara
	//GameObject* marco = addGameObject();
	//marco->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 103, WIN_HEIGHT* 2 / 3 - 44), Vector2D(0, 0), 190, 90);
	//auto An = marco->addComponent<Animator>(SDLApplication::getTexture("Marco"),
	//	BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);
	//An->attachToCamera();

	//auto but = addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 2/ 3),
	//	EXIT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS, marco);
	//but->getComponent<Animator>()->attachToCamera();

	SDLApplication::newScene<GameOverScene>();
}