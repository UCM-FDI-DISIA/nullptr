#include "BattleScene.h"
#include "../components/RangeBehavior.h"
#include "../components/MeleeBehaviour.h"

// Constructora
BattleScene::BattleScene(int a) : GameState() {
	cout << "Has entrado en la escena de Batalla" << endl;
  
	// Quitar cuando se cree el mapa de combate
	floor = addGameObject();
	floor->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH*2, WIN_HEIGHT*2);
	floor->addComponent<Image>(SDLApplication::getTexture("FloorPast"));
	//Añadimos el jugador
	player = addGameObject<Player>();
	camera->startFollowObject(player);
	//Añadimos el enemigo a distancia y le asignamos su posicion del vector
	RangedEnemy* rEn = addGameObject<RangedEnemy>(Vector2D(0, 0), 50, player);
	enemies.push_back(rEn);
	rEn->getComponent<RangeBehavior>()->setEnemyPosition(prev(enemies.end()));

	MeleeEnemy* mEn = addGameObject<MeleeEnemy>(Vector2D(0, 0), 50, player);
	enemies.push_back(mEn);
	mEn->getComponent<MeleeBehaviour>()->setEnemyPosition(prev(enemies.end()));

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
	SDLApplication::newScene<GameOverScene>();
}