#include "ChestScene.h"
#include "../core/SDLApplication.h"
#include "../components/General Components/CallbackDelayer.h"

ChestScene::ChestScene() : NodeScene() {
	cout << "Has entrado en la escena de Cofre" << endl;

	GameObject* background = addGameObject(_grp_GENERAL);
	background->addComponent<Transform>(Vector2D(), Vector2D(), Constant::getInt("WIN_WIDTH"), Constant::getInt("WIN_HEIGHT"));
	background->addComponent<Image>(SDLApplication::getTexture("ChestBackground"));

	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>(mainMenu, Vector2D(Constant::getFloat("WIN_WIDTH") / 2 - 79, (Constant::getFloat("WIN_HEIGHT") / 4) + 50), aI);

	 chestAI = new AnimatorInfo("GachaChest",
		SDLApplication::getTexture("GachaChest")->width(),
		SDLApplication::getTexture("GachaChest")->height(),
		46,
		26,
		1, 7);

	gachaButton = addGameObject(_grp_GENERAL);
	gachaButton->addComponent<Transform>(Vector2D(Constant::getFloat("WIN_WIDTH") / 2 - 79, (Constant::getFloat("WIN_HEIGHT") / 4) + 150), Vector2D(), chestAI->fw * 5, chestAI->fh * 5);
	
	
	auto anim = gachaButton->addComponent<Animator>(SDLApplication::getTexture("GachaChest"), chestAI->fw, chestAI->fh, chestAI->rows, chestAI->cols);
	
	anim->createAnim(ONOUT, 0, 0, ONCLICK_ONOUT_SPEED, -1);
	anim->createAnim(ONOVER, 0, 0, ONOVER_SPEED, -1);
	gachaButton->addComponent<ButtonComponent>([&, gb = gachaButton]() {gacha(gb);},nullptr, -1);
	
}
ChestScene:: ~ChestScene()
{
	delete chestAI;
}

void ChestScene::mainMenu() {
	SDLApplication::returnToMapScene();	
}

void ChestScene::gacha(GameObject* obj) {

	if (alreadyClicked) return;
	//Sacamos el vector de reliquias disponibles
	std::cout << "CLICK!\n";

	gachaButton->setAlive(false);
	GameObject* animation = addGameObject();
	animation->addComponent<Transform>(Vector2D(Constant::getFloat("WIN_WIDTH") / 2 - 79, (Constant::getFloat("WIN_HEIGHT") / 4) + 150), Vector2D(), chestAI->fw * 5, chestAI->fh * 5);
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
		cout << "Entraste" << "\n";
		//Sacamos un random entre 0 y su maximo
		int Rand = rand() % aux.size();

		//Sacamos la reliquia con la key que nos dan
		Relic* item = SDLApplication::instance()->getRelic(aux[Rand]);

		//Asignarsela al jugador
		PlayerData::instance()->addRelic(item);

		//Assign item (a�adir sprite a la escena y vivir feliz)
		GameObject* sprite = addGameObject(_grp_GENERAL);
		sprite->addComponent<Transform>(Vector2D(Constant::getFloat("WIN_WIDTH") / 2 - 79 + (26 * 5 / 2), (Constant::getFloat("WIN_HEIGHT") / 4) + (46 * 5 / 2)), Vector2D(), Constant::getInt("CHEST_BUTTON_HEIGHT"), Constant::getInt("CHEST_BUTTON_WIDTH"), 0);
		sprite->addComponent<Image>(item->texture);

		cout << item->description << "\n";


		//Borrar del vector
		auto it = aux.begin();
		std::advance(it, Rand);
		aux.erase(it);

		//Setear la nueva lista de items a player data
		PlayerData::instance()->setAvailableItems(aux);
		
	}
}
