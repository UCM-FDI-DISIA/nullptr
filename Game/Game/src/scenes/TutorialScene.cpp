#include "TutorialScene.h"

TutorialScene::TutorialScene(BattleType bt) : BattleScene(bt), current(Movimiento), screen(nullptr), 
		popup(nullptr), testEnemy(nullptr), tuto(nullptr) {
	cout << "ESTAS EN EL TUTORIAL" << endl;
}

void TutorialScene::activatePopUp() {
	// Le impedimos el movimiento y el ataque
	player->getComponent<PlayerInputComponent>()->setCanMove(false);
	player->getComponent<PlayerInputComponent>()->setCanAttack(false);

	// Objeto que cubre la pantalla
	screen = addGameObject(_grp_TUTORIAL);
	screen->addComponent<Transform>(Vector2D(), VECTOR_ZERO, WIN_WIDTH, WIN_HEIGHT);
	screen->addComponent<Image>(&sdlutils().images().at("Screen"))->attachToCamera();
}

void TutorialScene::deactivatePopUp() {
	screen->setAlive(false);
	popup->setAlive(false);
}