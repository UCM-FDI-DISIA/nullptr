#include "ChestScene.h"
#include "../core/SDLApplication.h"
#include "../components/General Components/CallbackDelayer.h"

ChestScene::ChestScene() : NodeScene() {
	// Fondo
	GameObject* background = addGameObject(_grp_GENERAL);
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("ChestBackground"));

	// Struct info de animación del cofre
	 chestAI = new AnimatorInfo(CHEST_TEXTURE,
		SDLApplication::getTexture(CHEST_TEXTURE)->width(),
		SDLApplication::getTexture(CHEST_TEXTURE)->height(),
		CHEST_SPRITE_WIDTH,
		CHEST_SPRITE_HEIGHT,
		5, 5);

	// -- COFRE --
	// Objeto
	gachaButton = addGameObject(_grp_GENERAL);
	gachaButton->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 40, WIN_HEIGHT / 4 + 165), VECTOR_ZERO,
		chestAI->fw * 6, chestAI->fh * 6);
	// Animator
	auto anim = gachaButton->addComponent<Animator>(SDLApplication::getTexture(CHEST_TEXTURE), chestAI->fw,
		chestAI->fh, chestAI->rows, chestAI->cols);
	anim->createAnim(ONOUT, 0, 12, 9, -1);
	anim->createAnim(ONOVER, 13, 13, ONOVER_SPEED, -1);
	// Componente botón
	gachaButton->addComponent<ButtonComponent>([&, gb = gachaButton]() {gacha(gb);});
}

ChestScene:: ~ChestScene() {
	delete chestAI;
}

void ChestScene::gacha(GameObject* obj) {
	// Desactivar botón
	gachaButton->setAlive(false);

	// Añadir nuevo objeto con animación de cofre abriéndose
	GameObject* animation = addGameObject();
	animation->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 40, WIN_HEIGHT / 4 + 165), VECTOR_ZERO,
		chestAI->fw * 6, chestAI->fh * 6);
	auto anim = animation->addComponent<Animator>(SDLApplication::getTexture(CHEST_TEXTURE),
		chestAI->fw, chestAI->fh, chestAI->rows, chestAI->cols);
	anim->createAnim(ONCLICK, 14, 20, 10, 1);
	anim->play(ONCLICK);

	// Objeto que llamará a una función tras X tiempo
	GameObject* delay = addGameObject();
	delay->addComponent<CallbackDelayer>([&]() {spawnNewItem(); }, 685);
}

void ChestScene::spawnNewItem() {
	// Sacamos el vector de reliquias disponibles
	vector<string> aux = PlayerData::instance()->getAvailableItems();

	// Si hay items disponibles
	if (aux.size() > 0) {
		// Sacamos un random entre 0 y su maximo
		int Rand = rand() % aux.size();

		// Sacamos la reliquia con la key que nos dan
		Relic* item = SDLApplication::instance()->getRelic(aux[Rand]);

		// Asignarsela al jugador
		PlayerData::instance()->addRelic(item);

		// Assign item (a�adir sprite a la escena y vivir feliz)
		GameObject* sprite = addGameObject(_grp_GENERAL);
		sprite->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79 + 90, WIN_HEIGHT / 4 + 45),
			VECTOR_ZERO, 32 * 4, 32 * 4);
		sprite->addComponent<Image>(item->texture);

		// Destellos
		GameObject* sparkles = addGameObject(_grp_GENERAL);
		sparkles->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 79 + 74, WIN_HEIGHT / 4 + 25),
			VECTOR_ZERO, 32 * 5, 32 * 5);
		auto anim = sparkles->addComponent<Animator>(SDLApplication::getTexture(SPARKLES_TEXTURE),
			32, 32, 3, 2);
		anim->createAnim(SPARKLES_TEXTURE, 0, 5, 12, 2);
		anim->play(SPARKLES_TEXTURE);

		// Borrar del vector
		auto it = aux.begin();
		advance(it, Rand);
		aux.erase(it);

		// Setear la nueva lista de items a player data
		PlayerData::instance()->setAvailableItems(aux);

		// Botón salir
		AnimatorInfo aI = AnimatorInfo(EXIT);
		addGameObject<Button>([]() { SDLApplication::returnToMapScene(); },
			Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH - 30, WIN_HEIGHT - MM_BUTTON_HEIGHT - 30), aI);
	}
}
