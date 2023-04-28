#include "TutorialScene.h"

TutorialScene::TutorialScene(BattleType bt) : BattleScene(bt, true), current(Movimiento), screen(nullptr), 
		testEnemy(nullptr), tuto(nullptr), tutoPopUp(nullptr), text(nullptr), button(nullptr) {

	// Le impedimos el movimiento y el ataque
	player->getComponent<PlayerInputComponent>()->setCanMove(false);
	player->getComponent<PlayerInputComponent>()->setCanAttack(false);
	pointer->setShowPointer(false);

	CardComponent* a = player->getComponent<CardComponent>();

	//Añadimos el controlador del tutorial
	GameObject* tc = addGameObject();
	tutorialController = tc->addComponent<TutorialComponent>([&]() { activatePopUp(); }, getSteps());
}

void TutorialScene::notifyDiscard() {
	tutorialController->setDiscarted(true);
	tutorialController->setCurrentStep((Pasos)current);
}

void TutorialScene::activateInput() {
	player->getComponent<PlayerInputComponent>()->setCanMove(true);
}

void TutorialScene::addCard() {
	// ENSEÑAMOS LA CARTA (LA ESPADA)
	createHand(player->getComponent<CardComponent>());
	player->getComponent<PlayerInputComponent>()->setCanAttack(true);
}

void TutorialScene::explainCardSystem() {
	player->getComponent<CardComponent>()->setInitialDeck();
	createCounters(player->getComponent<CardComponent>());
}

void TutorialScene::addMeleeEnemy() {
	// AÑADIMOS UN ENEMIGO A LA ESCENA
	Vector2D spawnPos = player->getComponent<Transform>()->getPos() + Vector2D(MELEE_ENEMY_WIDTH + 50, 0);
	GameObject* enemy = addGameObject<MeleeEnemy>(_grp_ENEMIES, spawnPos, MELEE_LIFE, player);
}

void TutorialScene::showAbility() {
	// 
}

void TutorialScene::showDrops() {

}

void TutorialScene::showPortalCharges() {

}

// Activa el popup
void TutorialScene::activatePopUp() {
	if (current == 2) {
		int i = 0;
	}
	tutorialController->setCurrentStep((Pasos)current);
	// Le impedimos el movimiento y el ataque
	player->getComponent<PlayerMovementComponent>()->setDirection(Vector2D());
	player->getComponent<PlayerInputComponent>()->setCanMove(false);
	player->getComponent<PlayerInputComponent>()->setCanAttack(false);

	// Mostrar puntero de ratón
	pointer->setShowPointer(true);
	
	// Objeto que cubre la pantalla
	screen = addGameObject(_grp_UI);
	screen->addComponent<Transform>(Vector2D(), VECTOR_ZERO, WIN_WIDTH, WIN_HEIGHT);
	screen->addComponent<Image>(&sdlutils().images().at("Screen"))->attachToCamera();

	// Imagen de tuto (cambiar luego t->width por constantes)
	Texture* t = &sdlutils().images().at("TutoTalking");
	tutoPopUp = addGameObject(_grp_UI);
	tutoPopUp->addComponent<Transform>(Vector2D(WIN_WIDTH/2 - t->width() * PIXEL_WIDTH /2, 0), Vector2D(), t->width() * PIXEL_WIDTH, t->height()/2 * PIXEL_HEIGHT);
	Animator* anim = tutoPopUp->addComponent<Animator>(t, 376, 284, 2, 1);
	anim->attachToCamera();
	anim->createAnim("idle", 0, 1, 2, -1);
	anim->play("idle");

	// Boton
	AnimatorInfo aI = AnimatorInfo(EXIT);
	button = addGameObject<Button>(_grp_UI, [&]() { deactivatePopUp(); }, Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2, WIN_HEIGHT - MM_BUTTON_HEIGHT - 10), aI);
	button->getComponent<Animator>()->attachToCamera();
}

// Desactiva el popup
void TutorialScene::deactivatePopUp() {
	// Objeto tuto
	if (tuto == nullptr) tuto = addGameObject<Tuto>(_grp_UI, player->getComponent<Transform>());
	player->getComponent<PlayerInputComponent>()->setCanMove(true);
	// Desactivar
	screen->setAlive(false);
	button->setAlive(false);
	tutoPopUp->setAlive(false);
	//text->setAlive(false);

	screen = nullptr;
	button = nullptr;
	tutoPopUp = nullptr;
	text = nullptr;

	tutorialController->doStep();
	current++;
}

// Devuelve los callbacks con sus respectivos tiempos
vector<pair<CallBack, double>> TutorialScene::getSteps() {
	vector<pair<CallBack, double>> steps;

	steps.push_back({ [&]() {activateInput(); }, 5 });
	steps.push_back({ [&]() {addCard(); }, -1 });
	steps.push_back({ [&]() {explainCardSystem(); }, 2 });
	steps.push_back({ [&]() {addMeleeEnemy(); }, -1 });
	steps.push_back({ [&]() {showAbility(); }, 5 });
	steps.push_back({ [&]() {showDrops(); }, 5 });
	steps.push_back({ [&]() {showPortalCharges(); }, 5 });
	return steps;
}