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
	
	//Añadimos la barra de vida y su marco (con sus componentes y los anclamos a la camara)
	vida = addGameObject();
	barraVida = addGameObject();

	barraVida->addComponent<Transform>(LIFEBAR_POSITION, LIFEBAR_VELOCITY, LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	vida->addComponent<Transform>(LIFE_POSITION, LIFE_VELOCITY, LIFE_WIDTH, LIFE_HEIGHT);
	
	barraVida->addComponent<Image>(SDLApplication::getTexture(LIFEBAR));
	vida->addComponent<Image>(SDLApplication::getTexture(LIFEFRAME));

	barraVida->getComponent<Image>()->attachToCamera();
	vida->getComponent<Image>()->attachToCamera();

	//Creamos el jugador e informamos a la camara de que debe seguirle
	player = addGameObject<Player>();
	camera->startFollowObject(player);

	//Añadimos 2 enemigos de prueba
	enemies.push_back(
		addGameObject<MeleeEnemy>(VECTOR_ZERO, 50, player)
	);
	/*enemies.push_back(
		addGameObject<MeleeEnemy>(VECTOR_ZERO, 50, player)
	);*/
  
	//Añadimo sun boton de salir
	Button* MainMenu = addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(BUTTON_FRAME_SPRITE_WIDTH + 10, BUTTON_SPRITE_HEIGHT + 10),
		EXIT, BUTTON_SPRITE_WIDTH * 4, BUTTON_SPRITE_HEIGHT * 4, BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_SPRITE_ROWS, BUTTON_SPRITE_COLUMS);

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