#include "ChestScene.h"
#include "../core/SDLApplication.h"

ChestScene::ChestScene() : NodeScene() {
	cout << "Has entrado en la escena de Cofre" << endl;

	GameObject* background = addGameObject(_grp_GENERAL);
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("ChestBackground"));

	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>(mainMenu, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);

	AnimatorInfo chestAI = AnimatorInfo("GachaChest",
		SDLApplication::getTexture("GachaChest")->width(),
		SDLApplication::getTexture("GachaChest")->height(),
		46,
		26,
		1, 7);

	
	GameObject* gachaButton = addGameObject(_grp_GENERAL);
	gachaButton->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 150), VECTOR_ZERO, chestAI.fw * 5, chestAI.fh * 5);
	
	
	auto anim = gachaButton->addComponent<Animator>(SDLApplication::getTexture("GachaChest"), chestAI.fw, chestAI.fh, chestAI.rows, chestAI.cols);
	
	anim->createAnim(ONOUT, 0, 0, ONCLICK_ONOUT_SPEED, -1);
	anim->createAnim(ONOVER, 0, 0, ONOVER_SPEED, -1);
	anim->createAnim(ONCLICK, 0, 6, 10, 1);

	gachaButton->addComponent<ButtonComponent>([&, gb=gachaButton]() {gacha(gb); }, SDLApplication::instance());
	
	/*
	AnimatorInfo aI = AnimatorInfo(key);
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), MM_BUTTONFRAME_WIDTH, MM_BUTTONFRAME_HEIGHT);
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols);

	// Crear boton
	addGameObject<Button>(_cb, SDLApplication::instance(), _bPos, aI, frame);
	
	*/
	
}

void ChestScene::mainMenu() {
	SDLApplication::returnToMapScene();	
}

void ChestScene::gacha(GameObject* obj) {

	if (alreadyClicked) return;
	//Sacamos el vector de reliquias disponibles
	std::cout << "CLICK!\n";
	std::vector<std::string> aux = PlayerData::instance()->getAvailableItems();

	if (aux.size() > 0) {
		cout << "Entraste" << "\n";
		//Sacamos un random entre 0 y su maximo
		int Rand = rand() % aux.size();

		//Sacamos la reliquia con la key que nos dan
		Relic* item = SDLApplication::instance()->getRelic(aux[Rand]);

		//Asignarsela al jugador
		PlayerData::instance()->addRelic(item);

		//Assign item (añadir sprite a la escena y vivir feliz)
		GameObject* sprite = addGameObject(_grp_GENERAL);
		sprite->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79 + (26 * 5 / 2), (WIN_HEIGHT / 4) + (46 * 5 / 2)), VECTOR_ZERO, CHEST_BUTTON_HEIGHT, CHEST_BUTTON_WIDTH, 0);
		sprite->addComponent<Image>(item->texture);

		cout << item->description << "\n";


		//Borrar del vector
		auto it = aux.begin();
		std::advance(it, Rand);
		aux.erase(it);

		//Setear la nueva lista de items a player data
		PlayerData::instance()->setAvailableItems(aux);
		//obj->removeComponent<ButtonComponent>();
		alreadyClicked = true;
	}
	
}