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
		//Relic* item = SDLApplication::instance()->getRelic(aux[Rand]);
		Relic* item = SDLApplication::instance()->getRelic(aux[9]);

		// Asignarsela al jugador
		PlayerData::instance()->addRelic(item);

		// Assign item (a�adir sprite a la escena y vivir feliz)
		relicUI(item);

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

void ChestScene::relicUI(Relic* r) {
	// Color blanco
	SDL_Color white; white.r = 255; white.g = 255; white.b = 255;

	// RELIQUIA ----------
	relicImage(r);

	// NOMBRE ----------
	relicName(r, white);

	// ESTADÍSTICAS ----------
	relicInfo(r, white);
}

void ChestScene::relicInfo(Relic* r, SDL_Color color) {
	// Marco
	GameObject* infoFrame = addGameObject();
	infoFrame->addComponent<Transform>(Vector2D(WIN_WIDTH - 80 * 4.2 / 1 - 60, WIN_HEIGHT / 4 + 29),
		VECTOR_ZERO, 80 * 4.2 / 1, 70 * 4.2 / 1);
	infoFrame->addComponent<Image>(SDLApplication::getTexture("ItemInfoFrame"));

	// Era
	GameObject* era = addGameObject();
	auto tr = era->addComponent<Transform>(Vector2D(), VECTOR_ZERO, 1, 1);
	string completeEra = "Era ";
	if (r->era == "F") completeEra += "Futuro";
	else if (r->era == "R") completeEra += "Presente";
	else completeEra += "Pasado";
	era->addComponent<TextComponent>(&sdlutils().fonts().at("SILKSCREEN_REGULAR"), completeEra, color);
	tr->setPos(Vector2D(WIN_WIDTH - 80 * 4.2 / 1 - 60 + (80 * 4.2 / 1) / 2 - tr->getWidth() / 2,
		WIN_HEIGHT / 4 + 45));

	// Vida
	GameObject* health = addGameObject();
	tr = health->addComponent<Transform>(Vector2D(), VECTOR_ZERO, 1, 1);
	standarizeText(health, r->health, color);
	tr->setPos(Vector2D(WIN_WIDTH - 80 * 4.2 / 1 - 60 + (80 * 4.2 / 1) / 2 - tr->getWidth() / 2,
		WIN_HEIGHT / 4 + 45 + 45));

	// Movimiento
	GameObject* movement = addGameObject();
	tr = movement->addComponent<Transform>(Vector2D(), VECTOR_ZERO, 1, 1);
	standarizeText(movement, r->movementVelocity, color);
	tr->setPos(Vector2D(WIN_WIDTH - 80 * 4.2 / 1 - 60 + (80 * 4.2 / 1) / 2 - tr->getWidth() / 2,
		WIN_HEIGHT / 4 + 45 + 45 * 2));

	// Cadencia
	GameObject* cadency = addGameObject();
	tr = cadency->addComponent<Transform>(Vector2D(), VECTOR_ZERO, 1, 1);
	standarizeText(cadency, r->cadencyMult, color);
	tr->setPos(Vector2D(WIN_WIDTH - 80 * 4.2 / 1 - 60 + (80 * 4.2 / 1) / 2 - tr->getWidth() / 2,
		WIN_HEIGHT / 4 + 45 + 45 * 3));

	// Mana
	GameObject* mana = addGameObject();
	tr = mana->addComponent<Transform>(Vector2D(), VECTOR_ZERO, 1, 1);
	standarizeText(mana, r->mana, color);
	tr->setPos(Vector2D(WIN_WIDTH - 80 * 4.2 / 1 - 60 + (80 * 4.2 / 1) / 2 - tr->getWidth() / 2,
		WIN_HEIGHT / 4 + 45 + 45 * 4));

	// Cadencia
	GameObject* attack = addGameObject();
	tr = attack->addComponent<Transform>(Vector2D(), VECTOR_ZERO, 1, 1);
	standarizeText(attack, r->attackMult, color);
	tr->setPos(Vector2D(WIN_WIDTH - 80 * 4.2 / 1 - 60 + (80 * 4.2 / 1) / 2 - tr->getWidth() / 2,
		WIN_HEIGHT / 4 + 45 + 45 * 5));
}

void ChestScene::relicImage(Relic* r) {
	// Marco del objeto
	relic.second = addGameObject();
	relic.second->addComponent<Transform>(RELIC_FRAME_POS, VECTOR_ZERO, 38 * 4.2 / 1, 38 * 4.2 / 1);
	relic.second->addComponent<Image>(SDLApplication::getTexture("ItemFrame"));

	// Objeto
	relic.first = addGameObject();
	relic.first->addComponent<Transform>(RELIC_POS, VECTOR_ZERO, 32 * 4, 32 * 4);
	relic.first->addComponent<Image>(r->texture);

	// Destellos
	GameObject* sparkles = addGameObject();
	sparkles->addComponent<Transform>(RELIC_SPARKS_POS, VECTOR_ZERO, 32 * 5, 32 * 5);
	auto anim = sparkles->addComponent<Animator>(SDLApplication::getTexture(SPARKLES_TEXTURE), 32, 32, 3, 2);
	anim->createAnim(SPARKLES_TEXTURE, 0, 5, 12, 2); anim->play(SPARKLES_TEXTURE);
}

void ChestScene::relicName(Relic* r, SDL_Color color) {
	// Marco y texto
	name.second = addGameObject();	// Marco - second
	name.first = addGameObject();	// Texto - first

	// Crear el texto para obtener su width
	auto textTr = name.first->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, 1, 1);
	name.first->addComponent<TextComponent>(&sdlutils().fonts().at("SILKSCREEN_BOLD"), r->id, color);

	// Crear marco dependiente del tamaño del texto
	auto frameTr = name.second->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, textTr->getWidth() + 40, textTr->getHeight() + 20);
	name.second->addComponent<Image>(SDLApplication::getTexture("ItemNameFrame"));

	// Colocar el marco respecto al frame de la reliquia tras la transformación
	frameTr->setPos(RELIC_FRAME_POS - Vector2D(frameTr->getWidth() / 2 - (38 * 4.2 / 1) / 2, 55));

	// Colocar el texto respecto a este marco
	textTr->setPos(Vector2D(frameTr->getPos().getX() + 20, frameTr->getPos().getY() + 10));
}

void ChestScene::standarizeText(GameObject* g, int stat, SDL_Color color) {
	if (stat <= 0)
		g->addComponent<TextComponent>(&sdlutils().fonts().at("SILKSCREEN_REGULAR"), "0", color);
	else
		g->addComponent<TextComponent>(&sdlutils().fonts().at("SILKSCREEN_REGULAR"), "+" + to_string(stat), color);
}