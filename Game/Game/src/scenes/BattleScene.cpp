#include "BattleScene.h"
#include "../components/Enemy components/RangeBehaviour.h"
#include "../components/Enemy components/MeleeBehaviour.h"

// Constructora
BattleScene::BattleScene(battleType t_) : GameState(), type(t_) {  
	//Suelo
	floor = addGameObject();
	floor->addComponent<Transform>(Vector2D(50, 50), FLOOR_PAST_VELOCITY, FLOOR_WIDTH, FLOOR_HEIGHT);
	//Selección de textura
	switch (type) {
	case _PASTBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("PastFloor"));
		break;
	case _PRESENTBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("PresentFloor"));
		break;
	case _FUTUREBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("FutureFloor"));
		break;
	case _BOSSBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("BossFloor"));
		break;
	}
	
	//Creamos el jugador e informamos a la camara de que debe seguirle
	player = addGameObject<Player>(_grp_PLAYER);
	camera->startFollowObject(player);

	// Generador de enemigos
	enemyGenerator = addGameObject();
	enemyGenerator->addComponent<EnemyGenerator>(player, this);
	
	// - UI -
	// Añadimos un boton de salir
	AnimatorInfo aI = AnimatorInfo(EXIT);
	Button* MainMenu = addGameObject<Button>([]() {	SDLApplication::newScene<MainMenuScene>(); }, SDLApplication::instance(), Vector2D(), aI);
	MainMenu->getComponent<Animator>()->attachToCamera();

	// Nos guardamos una referencia al componente de cartas del player
	CardComponent* cardComp = player->getComponent<CardComponent>();
	HealthComponent* healthComp = player->getComponent<HealthComponent>();

	// Añadimos el de estadísitcas
	statistics = addGameObject<StatisticsUI>(healthComp->getLife(), cardComp->getMana());

	// Creamos los contadores de cartas y linkeamos el componente con el contador de mazo par ala animacion de barajar
	auto gO = addGameObject<CardCounter>(true, cardComp);
	addGameObject<CardCounter>(false, cardComp);
	cardComp->setCounter(gO);
	// Añadimos el objeto que muestra la mano de cartas en la UI
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

void BattleScene::mainMenu() {
	SDLApplication::newScene<MainMenuScene>();
}

void BattleScene::OnPlayerDies() {
	SDLApplication::newScene<GameOverScene>();
}

void BattleScene::OnPlayerDamage(float value) {
	OnHealthChanges(value);
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

// Llamar al cambio del valor de maná
void BattleScene::OnManaChanges(float value) {
	//manaBar->getComponent<BarComponent>()->changeBar();
	statistics->OnManaChanges(value);
}

void BattleScene::OnHealthChanges(float value) {
	//healthBar->getComponent<BarComponent>()->changeBar();
	statistics->OnHealthChanges(value);
}