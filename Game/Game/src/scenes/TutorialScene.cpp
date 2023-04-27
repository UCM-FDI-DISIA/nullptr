#include "TutorialScene.h"

TutorialScene::TutorialScene(BattleType bt) : BattleScene(bt, true), current(Movimiento), screen(nullptr), 
		popup(nullptr), testEnemy(nullptr), tuto(nullptr) {

	// Le impedimos el movimiento y el ataque
	player->getComponent<PlayerInputComponent>()->setCanMove(true);
	player->getComponent<PlayerInputComponent>()->setCanAttack(false);

	//Añadimos el controlador del tutorial
	tutorialController = addGameObject();
	tutorialController->addComponent<TutorialComponent>(this);

	//Objeto tuto
	tuto = addGameObject<Tuto>(_grp_UI, player->getComponent<Transform>());
}

void TutorialScene::activatePopUp() {
	// Le impedimos el movimiento y el ataque
	player->getComponent<PlayerMovementComponent>()->setDirection(Vector2D());
	player->getComponent<PlayerInputComponent>()->setCanMove(false);
	player->getComponent<PlayerInputComponent>()->setCanAttack(false);

	pointer->setShowPointer(false);

	//// Objeto que cubre la pantalla
	//screen = addGameObject(_grp_TUTORIAL);
	//screen->addComponent<Transform>(Vector2D(), VECTOR_ZERO, WIN_WIDTH, WIN_HEIGHT);
	//screen->addComponent<Image>(&sdlutils().images().at("Screen"))->attachToCamera();
}

void TutorialScene::deactivatePopUp() {
	screen->setAlive(false);
	popup->setAlive(false);
}