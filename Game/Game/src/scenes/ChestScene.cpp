#include "ChestScene.h"
#include "../core/SDLApplication.h"
#include "../components/General Components/CallbackDelayer.h"

ChestScene::ChestScene() : NodeScene() {
	GameObject* background = addGameObject(_grp_GENERAL);
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("ChestBackground"));

	AnimatorInfo aI = AnimatorInfo(EXIT);
	Button* exitButton = addGameObject<Button>([]() { SDLApplication::returnToMapScene(); }, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);

	 chestAI = new AnimatorInfo("GachaChest",
		SDLApplication::getTexture("GachaChest")->width(),
		SDLApplication::getTexture("GachaChest")->height(),
		46,
		26,
		1, 7);

	gachaButton = addGameObject(_grp_GENERAL);
	gachaButton->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 150), VECTOR_ZERO, chestAI->fw * 5, chestAI->fh * 5);
	
	
	auto anim = gachaButton->addComponent<Animator>(SDLApplication::getTexture("GachaChest"), chestAI->fw, chestAI->fh, chestAI->rows, chestAI->cols);
	
	anim->createAnim(ONOUT, 0, 0, ONCLICK_ONOUT_SPEED, -1);
	anim->createAnim(ONOVER, 0, 0, ONOVER_SPEED, -1);
	anim->createAnim(ONCLICK, 0, 6, 10, 1);

	gachaButton->addComponent<ButtonComponent>([&, gb = gachaButton, eB = exitButton]() { gacha(gb); eB->setAsCurrentButton(); })->setAsCurrentButton();

}
ChestScene:: ~ChestScene()
{
	delete chestAI;
}


void ChestScene::gacha(GameObject* obj) {

	if (alreadyClicked) return;
	//Sacamos el vector de reliquias disponibles
#ifdef _DEBUG
	std::cout << "CLICK!\n";
#endif

	gachaButton->setAlive(false);
	GameObject* animation = addGameObject();
	animation->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 150), VECTOR_ZERO, chestAI->fw * 5, chestAI->fh * 5);
	auto anim = animation->addComponent<Animator>(SDLApplication::getTexture("GachaChest"), chestAI->fw, chestAI->fh, chestAI->rows, chestAI->cols);
	anim->createAnim("OnEnter", 0, 6, 10, 1);
	anim->play("OnEnter");

	GameObject* delay = addGameObject();
	delay->addComponent<CallbackDelayer>([&]() {spawnNewItem(); }, 500);

	alreadyClicked = true;
}

void ChestScene::spawnNewItem()
{
	std::vector<std::string> aux = PlayerData::instance()->getAvailableItems();

	if (aux.size() > 0) {
#ifdef _DEBUG
		cout << "Entraste" << "\n";
#endif
		//Sacamos un random entre 0 y su maximo
		int Rand = rand() % aux.size();

		//Sacamos la reliquia con la key que nos dan
		Relic* item = SDLApplication::instance()->getRelic(aux[Rand]);

		//Asignarsela al jugador
		PlayerData::instance()->addRelic(item);

		//Assign item (a�adir sprite a la escena y vivir feliz)
		GameObject* sprite = addGameObject(_grp_GENERAL);
		sprite->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79 + (26 * 5 / 2), (WIN_HEIGHT / 4) + (46 * 5 / 2)), VECTOR_ZERO, CHEST_BUTTON_HEIGHT, CHEST_BUTTON_WIDTH, 0);
		sprite->addComponent<Image>(item->texture);

#ifdef _DEBUG
		cout << item->description << "\n";
#endif

		//Borrar del vector
		auto it = aux.begin();
		std::advance(it, Rand);
		aux.erase(it);

		//Setear la nueva lista de items a player data
		PlayerData::instance()->setAvailableItems(aux);
		
	}
}
