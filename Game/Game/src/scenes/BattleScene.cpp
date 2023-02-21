#include "BattleScene.h"
#include "../components/RangeBehavior.h"
#include "../components/MeleeBehaviour.h"

// Constructora
BattleScene::BattleScene(battleType t_) : GameState(), type(t_) {
	cout << "Has entrado en la escena de Batalla" << endl;
  
	// Quitar cuando se cree el mapa de combate
	floor = addGameObject();
	floor->addComponent<Transform>(FLOOR_PAST_POSITION, FLOOR_PAST_VELOCITY, FLOOR_PAST_WIDTH, FLOOR_PAST_HEIGHT);
	floor->addComponent<Image>(SDLApplication::getTexture(FLOOR_PAST));
	
	vida = addGameObject();
	barraVida = addGameObject();

	barraVida->addComponent<Transform>(LIFEFRAME_POSITION, LIFEFRAME_VELOCITY, LIFEFRAME_WIDTH, LIFEFRAME_HEIGHT);
	vida->addComponent<Transform>(LIFE_POSITION, LIFE_VELOCITY, LIFE_WIDTH, LIFE_HEIGHT);
	
	barraVida->addComponent<Image>(SDLApplication::getTexture(LIFEFRAME));
	vida->addComponent<Image>(SDLApplication::getTexture(LIFE));

	barraVida->getComponent<Image>()->attachToCamera();
	vida->getComponent<Image>()->attachToCamera();


	player = addGameObject<Player>();
	camera->startFollowObject(player);


	enemies.push_back(
		addGameObject<RangedEnemy>(VECTOR_ZERO, 50, player)
	);
	enemies.push_back(
		addGameObject<MeleeEnemy>(VECTOR_ZERO, 50, player)
	);
  
	Button* MainMenu = addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(BUTTON_FRAME_SPRITE_WIDTH + 10, BUTTON_SPRITE_HEIGHT + 10),
		EXIT, MAINMENU_BUTTON_WIDTH, MAINMENU_BUTTON_HEIGHT, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);

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