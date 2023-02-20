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
	
	vida = addGameObject();
	barraVida = addGameObject();

	barraVida->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 + 138, 20), Vector2D(0, 0), 200, 30);
	vida->addComponent<Transform>(Vector2D(WIN_WIDTH/2 +125, 0), Vector2D(0, 0),213, 53);
	
	barraVida->addComponent<Image>(SDLApplication::getTexture("Life"));
	vida->addComponent<Image>(SDLApplication::getTexture("LifeBar"));

	barraVida->getComponent<Image>()->attachToCamera();
	vida->getComponent<Image>()->attachToCamera();


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
void BattleScene::update() {
	for (GameObject* gObj : gObjs) {
		gObj->update();
	}
	auto it = enemies.begin();
	while (it != enemies.end())
	{
		if ((*it)->isAlive() == false) {
			auto itAux = it;
			it = enemies.erase(itAux);
		}
		else it++;
	}
	refresh();
}
void BattleScene::mainMenu() {
	SDLApplication::newScene<MainMenuScene>();
}

vector<GameObject*>* BattleScene::getEnemies() {
	return &enemies;
}

void BattleScene::OnPlayerDies() {
	SDLApplication::newScene<GameOverScene>();
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