#include "ChestScene.h"
#include "../core/SDLApplication.h"
#include "../components/General Components/CallbackDelayer.h"

ChestScene::ChestScene() : NodeScene() {
	// Sonido
	chestOpening=&sdlutils().soundEffects().at(CHEST_OPENING_SOUND);
  
	// Fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture(CHEST_BG));

	// Struct info de animación del cofre
	 chestAI = new AnimatorInfo(CHEST_TEXTURE,
		SDLApplication::getTexture(CHEST_TEXTURE)->width(),
		SDLApplication::getTexture(CHEST_TEXTURE)->height(),
		CHEST_SPRITE_WIDTH,
		CHEST_SPRITE_HEIGHT,
		5, 5);

	// -- COFRE --
	// Objeto
	gachaButton = addGameObject();
	gachaButton->addComponent<Transform>(CHEST_POS, VECTOR_ZERO, chestAI->fw * 6, chestAI->fh * 6);
	// Animator
	auto anim = gachaButton->addComponent<Animator>(SDLApplication::getTexture(CHEST_TEXTURE), chestAI->fw,
		chestAI->fh, chestAI->rows, chestAI->cols);
	anim->createAnim(ONOUT, 0, 12, 9, -1);
	anim->createAnim(ONOVER, 13, 13, ONOVER_SPEED, -1);
	// Componente botón
	gachaButton->addComponent<ButtonComponent>([&, gb = gachaButton]() {gacha(gb);})->setAsDefaultButton();
}

ChestScene:: ~ChestScene() {
	delete chestAI;
}

void ChestScene::gacha(GameObject* obj) {
  // Reproducir sonido
  chestOpening->play();
  
	// Desactivar botón
	gachaButton->setAlive(false);

	// Añadir nuevo objeto con animación de cofre abriéndose
	GameObject* animation = addGameObject();
	animation->addComponent<Transform>(CHEST_POS, VECTOR_ZERO, chestAI->fw * 6, chestAI->fh * 6);
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

		// Mostrar en la interfaz
		relicUI(item);

		// Borrar del vector
		auto it = aux.begin();
		advance(it, Rand);
		aux.erase(it);

		// Setear la nueva lista de items a player data
		PlayerData::instance()->setAvailableItems(aux);

		// Botón salir
		AnimatorInfo aI = AnimatorInfo(EXIT);
		addGameObject<Button>([]() { SDLApplication::returnToMapScene(); }, CHEST_EXIT_BUTTON_POS, aI)->setAsCurrentButton();
	}
}

void ChestScene::relicUI(Relic* r) {
	// Color blanco
	SDL_Color white; white.r = 255; white.g = 255; white.b = 255;

	// RELIQUIA
	relicImage(r);

	// NOMBRE
	relicName(r, white);

	// ESTADÍSTICAS
	relicInfo(r, white);
}

void ChestScene::relicInfo(Relic* r, SDL_Color color) {
	// Marco
	GameObject* infoFrame = addGameObject();
	infoFrame->addComponent<Transform>(INFO_FRAME_POS, VECTOR_ZERO, INFO_FRAME_WIDTH, INFO_FRAME_HEIGHT);
	infoFrame->addComponent<Image>(SDLApplication::getTexture(INFO_FRAME));

	// Era
	GameObject* era = addGameObject();
	auto tr = era->addComponent<Transform>(Vector2D(), VECTOR_ZERO, 1, 1);
	string completeEra = getEraString(r->era);
	era->addComponent<TextComponent>(&sdlutils().fonts().at(FONT_SS_REG), completeEra, color);
	tr->setPos(INFO_FRAME_POS + Vector2D(INFO_FRAME_WIDTH / 2 - tr->getWidth() / 2, 15));

	// Vida
	createStat(r->health, "LifeSymbol", 70, color);

	// Movimiento
	createStat(r->speed, "SpeedSymbol", 140, color);

	// Cadencia
	createStat(r->fireRateMult, "CadenceSymbol", 210, color);

	// Mana
	createStat(r->mana, "ManaSymbol", 280, color);

	// Ataque
	createStat(r->attackMult, "AttackSymbol", 350, color);
}

void ChestScene::relicImage(Relic* r) {
	// Marco del objeto
	relic.second = addGameObject();
	relic.second->addComponent<Transform>(RELIC_FRAME_POS, VECTOR_ZERO, RELIC_FRAME_DIMS, RELIC_FRAME_DIMS);
	relic.second->addComponent<Image>(SDLApplication::getTexture(RELIC_FRAME));

	// Objeto
	relic.first = addGameObject();
	relic.first->addComponent<Transform>(RELIC_POS, VECTOR_ZERO, RELIC_DIMS, RELIC_DIMS);
	relic.first->addComponent<Image>(r->texture);

	// Destellos
	GameObject* sparkles = addGameObject();
	sparkles->addComponent<Transform>(RELIC_SPARKS_POS, VECTOR_ZERO, SPARKS_DIMS, SPARKS_DIMS);
	auto anim = sparkles->addComponent<Animator>(SDLApplication::getTexture(SPARKLES_TEXTURE), 32, 32, 3, 2);
	anim->createAnim(SPARKLES_TEXTURE, 0, 5, 12, 2); anim->play(SPARKLES_TEXTURE);
}

void ChestScene::relicName(Relic* r, SDL_Color color) {
	// Marco y texto
	name.second = addGameObject();	// Marco - second
	name.first = addGameObject();	// Texto - first

	// Crear el texto para obtener su width
	auto textTr = name.first->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, 1, 1);
	name.first->addComponent<TextComponent>(&sdlutils().fonts().at(FONT_SS_BOLD), r->id, color);

	// Crear marco dependiente del tamaño del texto
	auto frameTr = name.second->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO,
		textTr->getWidth() + NAME_DIMS_OFFSET, textTr->getHeight() + NAME_DIMS_OFFSET / 2);
	name.second->addComponent<Image>(SDLApplication::getTexture(NAME_FRAME));

	// Colocar el marco respecto al frame de la reliquia tras la transformación
	frameTr->setPos(RELIC_FRAME_POS - Vector2D(frameTr->getWidth() / 2 - RELIC_FRAME_DIMS / 2, 55));

	// Colocar el texto respecto a este marco
	textTr->setPos(Vector2D(frameTr->getPos().getX() + NAME_DIMS_OFFSET / 2,
		frameTr->getPos().getY() + NAME_DIMS_OFFSET / 4));
}

// Añade el componente de texto con un + o un 0 dependiendo del valor recibido
void ChestScene::standarizeText(GameObject* g, int stat, SDL_Color color) {
	if (stat <= 0)
		g->addComponent<TextComponent>(&sdlutils().fonts().at(FONT_SS_REG), "0", color);
	else
		g->addComponent<TextComponent>(&sdlutils().fonts().at(FONT_SS_REG), "+" + to_string(stat), color);
}

// Devuelve un string con la era correspondiente
string ChestScene::getEraString(string rEra) {
	string completeEra = "Del ";

	if (rEra == "F") completeEra += "Futuro";
	else if (rEra == "R") completeEra += "Presente";
	else completeEra += "Pasado";

	return completeEra;
}

// Crea una linea con el estado correspondiente
void ChestScene::createStat(int stat, string symbol, int yOffset, SDL_Color color) {
	// Variable auxiliar y objetos de img y texto vacíos
	Transform* tr = nullptr;
	GameObject* img = addGameObject();
	GameObject* txt = addGameObject();
	
	// Transform "vacio"
	tr = txt->addComponent<Transform>(Vector2D(), VECTOR_ZERO, 1, 1);

	// Objeto de texto y posición del mismo respecto a su tamaño
	standarizeText(txt, stat, color);
	tr->setPos(INFO_FRAME_POS + Vector2D(INFO_FRAME_WIDTH * 2.6 / 4 - tr->getWidth() / 2, yOffset));

	// Objeto imagen
	img->addComponent<Transform>(INFO_FRAME_POS + Vector2D(INFO_FRAME_WIDTH / 4 - SYMBOL_DIMENSIONS / 2 - 15, yOffset - 15),
		VECTOR_ZERO, SYMBOL_DIMENSIONS, SYMBOL_DIMENSIONS);
	img->addComponent<Image>(SDLApplication::getTexture(symbol));
}