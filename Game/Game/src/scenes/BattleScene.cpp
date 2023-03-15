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
	// Nos guardamos una referencia al componente de cartas del player
	CardComponent* cardComp = player->getComponent<CardComponent>();
	HealthComponent* healthComp = player->getComponent<HealthComponent>();

	// Añadimos el de estadísitcas
	hand = nullptr;
	cardContLeft = nullptr;
	cardContRight = nullptr;
	if (cardComp != nullptr) {
		statistics = nullptr;
		if (healthComp != nullptr) statistics = addGameObject<StatisticsUI>(_grp_UI, healthComp->getLife(), cardComp->getMana());
		
		// Creamos los contadores de cartas y linkeamos el componente con el contador de mazo par ala animacion de barajar
		cardContLeft = addGameObject<CardCounter>(_grp_UI, true, cardComp);
		cardContRight = addGameObject<CardCounter>(_grp_UI, false, cardComp);
		cardComp->setCounter(cardContLeft);

		// Añadimos el objeto que muestra la mano de cartas en la UI
		hand = addGameObject<HandUI>(_grp_UI, cardComp);
	}

	// El puntero sigue al player
	pointer->getComponent<PointerComponent>()->setFollowObject(player);
};

void BattleScene::OnPlayerDies() {
	PlayerData::instance()->resetMana();
	SDLApplication::newScene<GameOverScene>();
}

void BattleScene::OnPlayerDamage(float value) {
	onHealthChanges(value);
}

// CAMBIOS DE UI
// Llamar a cambiar la carta seleccionada de la UI
void BattleScene::changeUISelected(bool key, int number) {
	if (hand != nullptr) hand->changeSelected(key, number);
}

// Llamar a borrar una carta de la UI
void BattleScene::discardUI(deque<Card*>::iterator discarded) {
	if (hand != nullptr) hand->discard(discarded);
}

// Llamar a la creaci�n de la UI
void BattleScene::recreateUI() {
	if (hand != nullptr) hand->createUI();
}

// Llamar al cambio del valor de maná
void BattleScene::onManaChanges(float value) {
	if (statistics != nullptr) statistics->onManaChanges(value);
}

// Llamar al cambio del valor de maná
void BattleScene::onHealthChanges(float value) {
	if (statistics != nullptr) statistics->onHealthChanges(value);
}

// Llamar al cambio del valor de éter
void BattleScene::onEtherChanges(float value) {
	if (statistics != nullptr) statistics->onEtherChanges(value);
}