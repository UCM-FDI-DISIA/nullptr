#include "BattleScene.h"
#include "../components/Enemy components/RangeBehaviour.h"
#include "../components/Enemy components/MeleeBehaviour.h"
#include "../components/Player components/MannaBarComponent.h"

// Constructora
BattleScene::BattleScene(battleType t_) : GameState(), type(t_) {
	cout << "Has entrado en la escena de Batalla" << endl;
  
	// Quitar cuando se cree el mapa de combate
	floor1 = addGameObject();
	floor1->addComponent<Transform>(Vector2D(50,50), FLOOR_PAST_VELOCITY, 1500, 1080);
	floor1->addComponent<Image>(SDLApplication::getTexture("1"));
	floor1->getComponent<Image>()->setScrollFactor(0.5);

	floor2 = addGameObject();
	floor2->addComponent<Transform>(Vector2D(50, 50), FLOOR_PAST_VELOCITY, 1500, 1080);
	floor2->addComponent<Image>(SDLApplication::getTexture("2"));
	floor2->getComponent<Image>()->setScrollFactor(0.25);

	floor3 = addGameObject();
	floor3->addComponent<Transform>(Vector2D(50, 150), FLOOR_PAST_VELOCITY, 1500, 1080);
	floor3->addComponent<Image>(SDLApplication::getTexture("3"));
	floor3->getComponent<Image>()->setScrollFactor(0.20);

	//Creamos el jugador e informamos a la camara de que debe seguirle
	player = addGameObject<Player>();
	camera->startFollowObject(player);

	//Añadimos la barra de vida y su marco (con sus componentes y los anclamos a la camara)
	createLifeBar();
	createManaBar();

	//Añadimos 2 enemigos de prueba
	enemies.push_back(
		addGameObject<RangedEnemy>(VECTOR_ZERO, 50, player)
	);
	enemies.push_back(
		addGameObject<MeleeEnemy>(VECTOR_ZERO, 50, player)
	);
  

	AnimatorInfo aI = AnimatorInfo(EXIT);
	//Añadimo sun boton de salir
	Button* MainMenu = addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(BUTTON_FRAME_SPRITE_WIDTH + 10, BUTTON_SPRITE_HEIGHT + 10), aI);

	MainMenu->getComponent<Animator>()->attachToCamera();

	//Nos guardamos una referencia al componente de cartas del player
	CardComponent* cardComp = player->getComponent<CardComponent>();

	//Creamos los contadores de cartas y linkeamos el componente con el contador de mazo par ala animacion de barajar
	auto gO = addGameObject<CardCounter>(true, cardComp);
	addGameObject<CardCounter>(false, cardComp);
	cardComp->setCounter(gO);
	//Añadimos el objeto que muestra la mano de cartas en la UI
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

void BattleScene::OnManaChanges() {
	barraMana->getComponent<MannaBarComponent>()->changeBar();
}

void BattleScene::createLifeBar() {
	vida = addGameObject();
	barraVida = addGameObject();


	barraVida->addComponent<Transform>(LIFEBAR_POSITION, LIFEBAR_VELOCITY, BAR_WIDTH, BAR_HEIGHT);
	vida->addComponent<Transform>(LIFE_POSITION, LIFE_VELOCITY, LIFE_WIDTH, LIFE_HEIGHT);

	barraVida->addComponent<Image>(SDLApplication::getTexture(LIFEBAR));
	vida->addComponent<Image>(SDLApplication::getTexture(LIFEFRAME));

	barraVida->getComponent<Image>()->attachToCamera();
	vida->getComponent<Image>()->attachToCamera();
}

void BattleScene::createManaBar() {
	mana = addGameObject();
	barraMana = addGameObject();

	barraMana->addComponent<Transform>(MANABAR_POSITION, MANABAR_VELOCITY, BAR_WIDTH, BAR_HEIGHT);
	mana->addComponent<Transform>(MANA_POSITION, MANA_VELOCITY, LIFE_WIDTH, LIFE_HEIGHT);

	barraMana->addComponent<Image>(SDLApplication::getTexture(MANABAR));
	mana->addComponent<Image>(SDLApplication::getTexture(MANAFRAME));

	barraMana->getComponent<Image>()->attachToCamera();
	mana->getComponent<Image>()->attachToCamera();

	barraMana->addComponent<MannaBarComponent>(player->getComponent<CardComponent>());
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