#include "TutorialScene.h"
#include "../gameObjects/UI/HandUI.h"
#include "../gameObjects/UI/StatisticsUI.h"

TutorialScene::TutorialScene(BattleType bt) : BattleScene(bt, true), current(0), screen(nullptr), 
		testEnemy(nullptr), tuto(nullptr), tutoPopUp(nullptr), textOne(nullptr), textTwo(nullptr), button(nullptr) {
	SDLApplication::instance()->stopMainMusic();
	// Le impedimos el movimiento y el ataque
	PlayerInputComponent* pic = player->getComponent<PlayerInputComponent>();
	pic->setCanMove(false);
	pic->setCanAttack(false);
	pic->setCanUseAbility(false);
	pic->setCanExit(false);
	// Ocultamos el puntero
	pointer->setShowPointer(false);

	//Añadimos el controlador del tutorial
	GameObject* tc = addGameObject();
	tutorialController = tc->addComponent<TutorialComponent>([&]() { activatePopUp(); }, getSteps());
	enemyGenerator->getComponent<EnemyGenerator>()->setCanSpawn(false);
}

void TutorialScene::activateInput() {
	// Ocultamos el puntero y le permitimos moverse
	pointer->setShowPointer(false);
	player->getComponent<PlayerInputComponent>()->setCanMove(true);
	tutorialController->setPlayerCanMove(true);
}

void TutorialScene::addCard() {
	// Creamos la interfaz de la mano de cartas (solo tiene la espada)
	createHand(player->getComponent<CardComponent>());
}

void TutorialScene::explainCardSystem() {
	// Le damos las cartas del mazo inicial
	CardComponent* cc = player->getComponent<CardComponent>();
	cc->setInitialDeck();

	// Creamos los contadores de cartas y destruimos y volvemos a crear la mano
	createCounters(cc);
	hand->setAlive(false);
	hand = addGameObject<HandUI>(_grp_UI,cc);
}

void TutorialScene::addMeleeEnemy() {
	// AÑADIMOS UN ENEMIGO A LA ESCENA
	Vector2D spawnPos = player->getComponent<Transform>()->getPos() + Vector2D(MELEE_ENEMY_WIDTH + 200, 0);
	testEnemy = addGameObject<MeleeEnemy>(_grp_ENEMIES, spawnPos, MELEE_LIFE, player, 3, 0);
	// Y creamos la barra superior de la UI (bloqueamos el input de salir de partida)
	player->getComponent<PlayerInputComponent>()->setCanExit(false);
	createStatistics(player->getComponent<HealthComponent>(), player->getComponent<CardComponent>());
}

void TutorialScene::showAbility() {
	// Permitimos que pueda usar la habilidad de la carta
	player->getComponent<PlayerInputComponent>()->setCanUseAbility(true);
}

void TutorialScene::showDrops() {
	// Añado otro enemigo que me completará el éter necesario para salir en el proximo paso
	Vector2D spawnPos = player->getComponent<Transform>()->getPos() + Vector2D(MELEE_ENEMY_WIDTH + 200, 0);
	testEnemy = addGameObject<MeleeEnemy>(_grp_ENEMIES, spawnPos, MELEE_LIFE, player, 0, 100);
}

void TutorialScene::showPortalCharges() {
	// Permito al jugador salir de partida y seteo la referencia a la carga de portal en el input
	player->getComponent<PlayerInputComponent>()->setCanExit(true);
	player->getComponent<PlayerInputComponent>()->setPortalComponent(statistics->getPortalComp());
}

// Activa el popup
void TutorialScene::activatePopUp() {
	// Le impedimos el movimiento y el ataque
	player->getComponent<PlayerMovementComponent>()->setDirection(Vector2D());
	player->getComponent<PlayerInputComponent>()->setCanMove(false);
	player->getComponent<PlayerInputComponent>()->setCanAttack(false);
	pointer->getComponent<PointerComponent>()->discardFollowObject();

	// Mostrar puntero de ratón
	pointer->setShowPointer(true);
	
	// Objeto que cubre la pantalla
	screen = addGameObject(_grp_UI);
	screen->addComponent<Transform>(Vector2D(), VECTOR_ZERO, WIN_WIDTH, WIN_HEIGHT);
	screen->addComponent<Image>(&sdlutils().images().at(DARK_PLAIN_TEXTURE))->attachToCamera();

	// Imagen de tuto (cambiar luego t->width por constantes)
	tutoPopUp = addGameObject(_grp_UI);
	tutoPopUp->addComponent<Transform>(TUTO_POPUP_POS, Vector2D(), TUTO_POPUP_WIDTH, TUTO_POPUP_HEIGHT);
	Animator* anim = tutoPopUp->addComponent<Animator>(SDLApplication::getTexture(TUTO_TALKING_TEXTURE),
		TUTO_POPUP_SPRITE_WIDTH, TUTO_POPUP_SPRITE_HEIGHT, 2, 1);
	anim->attachToCamera();
	anim->createAnim("idle", 0, 1, 3, -1);
	anim->play("idle");

	// Mostar texto correspondiente
	showPopUpText();

	// Boton
	AnimatorInfo aI = AnimatorInfo(RESUME);
	button = addGameObject<Button>(_grp_UI, [&]() { deactivatePopUp(); }, RESUME_BUTTON_POS, aI);
	button->getComponent<Animator>()->attachToCamera();
	if (ih().isControllerConnected()) button->setAsCurrentButton();
}

// Desactiva el popup
void TutorialScene::deactivatePopUp() {
	// Objeto tuto
	if (tuto == nullptr) {
		tuto = addGameObject<Tuto>(_grp_UI, player->getComponent<Transform>());
		if (current >= 3) tuto->changeAnim(current);
	}
	else tuto->changeAnim(current);
	player->getComponent<PlayerInputComponent>()->setCanMove(true);

	// Desactivar
	screen->setAlive(false);
	button->setAlive(false);
	tutoPopUp->setAlive(false);
	textOne->setAlive(false);
	textTwo->setAlive(false);

	// Anulo referencias
	screen = nullptr;
	button = nullptr;
	tutoPopUp = nullptr;
	textOne = nullptr;
	textTwo = nullptr;

	// Realizo el lambda que toque y aumento el estado en el que estoy
	tutorialController->doStep();
	current++;

	// Si estoy en el paso 2 como minimo, debo permitir al jugador atacar y hacer que el puntero le siga
	if (current >= 2) {
		pointer->getComponent<PointerComponent>()->setFollowObject(player);
		player->getComponent<PlayerInputComponent>()->setCanAttack(true);
		if (current == 4 || current == 6) {
			hideTuto();
		}
	}
	tutorialController->setCanAdvance(true);
}

void TutorialScene::hideTuto() {
	tuto->setAlive(false);
	tuto = nullptr;
}

// Devuelve los callbacks con sus respectivos tiempos
vector<CallBack> TutorialScene::getSteps() {
	vector<CallBack> steps;

	steps.push_back([&]() {activateInput(); });
	steps.push_back([&]() {addCard(); });
	steps.push_back([&]() {explainCardSystem(); });
	steps.push_back([&]() {addMeleeEnemy(); });
	steps.push_back([&]() {showAbility(); });
	steps.push_back([&]() {showDrops(); });
	steps.push_back([&]() {showPortalCharges(); });
	return steps;
}

// Añade el texto correspondiente al popup
void TutorialScene::showPopUpText() {
	// Color del texto
	SDL_Color color = { 213, 180, 152 };
	Transform* tr = nullptr;

	// Añadir objeto con el componente transform y el de texto con el string adecuado
	textOne = addGameObject(_grp_UI);
	textTwo = addGameObject(_grp_UI);

	// Seleccionar texto
	// Primer texto
	tr = textOne->addComponent<Transform>(TUTO_POPUP_POS + TEXT_OFFSET, VECTOR_ZERO, TUTO_POPUP_WIDTH - 120, TUTO_POPUP_HEIGHT - 120);
	textOne->addComponent<TextComponent>(&sdlutils().fonts().at(FONT_SS_REG30), tutorialTexts[current * 2], color, true)->attachToCamera();

	// Segundo texto
	textTwo->addComponent<Transform>(Vector2D(tr->getPos().getX(), tr->getPos().getY() + tr->getHeight()), VECTOR_ZERO, TUTO_POPUP_WIDTH - 120, TUTO_POPUP_HEIGHT - 120);
	textTwo->addComponent<TextComponent>(&sdlutils().fonts().at(FONT_SS_REG30), tutorialTexts[current * 2 + 1], color, true)->attachToCamera();
}