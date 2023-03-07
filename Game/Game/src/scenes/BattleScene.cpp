#include "BattleScene.h"
#include "../components/Enemy components/RangeBehaviour.h"
#include "../components/Enemy components/MeleeBehaviour.h"

// Constructora
BattleScene::BattleScene(battleType t_) : GameState(), type(t_) {  
	// SUELO - Quitar cuando se cree el mapa de combate
	floor1 = addGameObject();
	floor1->addComponent<Transform>(Vector2D(50,50), FLOOR_PAST_VELOCITY, FLOOR_WIDTH,FLOOR_HEIGHT);
	floor1->addComponent<Image>(SDLApplication::getTexture("1"));
	floor1->getComponent<Image>()->setScrollFactor(0.5);

	floor2 = addGameObject();
	floor2->addComponent<Transform>(Vector2D(50, 50), FLOOR_PAST_VELOCITY, FLOOR_WIDTH, FLOOR_HEIGHT);
	floor2->addComponent<Image>(SDLApplication::getTexture("2"));
	floor2->getComponent<Image>()->setScrollFactor(0.25);

	floor3 = addGameObject();
	floor3->addComponent<Transform>(Vector2D(50, 150), FLOOR_PAST_VELOCITY, FLOOR_WIDTH, FLOOR_HEIGHT);
	floor3->addComponent<Image>(SDLApplication::getTexture("3"));
	floor3->getComponent<Image>()->setScrollFactor(0.20);

	//Creamos el jugador e informamos a la camara de que debe seguirle
	player = addGameObject<Player>();
	camera->startFollowObject(player);

	// Generador de enemigos
	//enemyGenerator = addGameObject();
	//enemyGenerator->addComponent<EnemyGenerator>(player, this);

	//Añadimos 2 enemigos de prueba
	enemies.push_back(
		addGameObject<RangedEnemy>(VECTOR_ZERO, 50, player)
	);
	/*enemies.push_back(
		addGameObject<MeleeEnemy>(VECTOR_ZERO, 50, player)
	);*/
	enemies.push_back(
		addGameObject<TankEnemy>(VECTOR_ZERO, 50, player)
	);
	
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