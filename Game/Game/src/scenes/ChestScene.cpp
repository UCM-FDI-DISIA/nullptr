#include "ChestScene.h"
#include "../core/SDLApplication.h"

ChestScene::ChestScene() : GameState() {
	cout << "Has entrado en la escena de Cofre" << endl;

	GameObject* background = addGameObject(_grp_GENERAL);
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("ChestBackground"));

	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);

	GameObject* Gacha = addGameObject(_grp_GENERAL);
	Gacha->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 150), VECTOR_ZERO, CHEST_BUTTON_HEIGHT, CHEST_BUTTON_WIDTH, 0);
	Gacha->addComponent<Image>(SDLApplication::getTexture("GachaChest"));
	Gacha->addComponent<Button>([&](){gacha();}, SDLApplication::instance());
	
}

void ChestScene::mainMenu() {
	SDLApplication::newScene<MapScene>();
}

void ChestScene::gacha() {
	//Sacamos el vector de reliquias disponibles
	std::vector<std::string> aux = PlayerData::instance()->getAvailableItems();

	//Sacamos un random entre 0 y su maximo
	int Rand = rand() % aux.size();

	//Sacamos la reliquia con la key que nos dan
	Relic* item = SDLApplication::instance()->getRelic(aux[Rand]);

	//Asignarsela al jugador
	PlayerData::instance()->addRelic(item);

	//Assign item (añadir sprite a la escena y vivir feliz)
	GameObject* sprite = addGameObject(_grp_GENERAL);
	sprite->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 150), VECTOR_ZERO, CHEST_BUTTON_HEIGHT, CHEST_BUTTON_WIDTH, 0);
	sprite->addComponent<Image>(item->texture);

	cout << item->description << "\n";


	//Borrar del vector
	auto it = aux.begin();
	std::advance(it, Rand);
	aux.erase(it);

	//Setear la nueva lista de items a player data
	PlayerData::instance()->setAvailableItems(aux);
}