#include "TutorialScene.h"

TutorialScene::TutorialScene(BattleType bt) : NodeScene(), type (bt) {
	//Fondo
	background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("BattleBackground"))->attachToCamera();
	background3 = addGameObject();
	background3->addComponent<Transform>(Vector2D(), Vector2D(), BATTLEBACKGROUND123_WIDTH, BATTLEBACKGROUND123_HEIGHT);
	background3->addComponent<Image>(SDLApplication::getTexture("BattleBackground3"))->setScrollFactor(BATTLEBACKGROUND3_SCROLLFACTOR);
	background2 = addGameObject();
	background2->addComponent<Transform>(Vector2D(), Vector2D(), BATTLEBACKGROUND123_WIDTH, BATTLEBACKGROUND123_HEIGHT);
	background2->addComponent<Image>(SDLApplication::getTexture("BattleBackground2"))->setScrollFactor(BATTLEBACKGROUND2_SCROLLFACTOR);
	background1 = addGameObject();
	background1->addComponent<Transform>(Vector2D(), Vector2D(), BATTLEBACKGROUND123_WIDTH, BATTLEBACKGROUND123_HEIGHT);
	background1->addComponent<Image>(SDLApplication::getTexture("BattleBackground1"))->setScrollFactor(BATTLEBACKGROUND1_SCROLLFACTOR);

	//Suelo
	floor = addGameObject();
	floor->addComponent<Transform>(Vector2D(50, 50), FLOOR_PAST_VELOCITY, FLOOR_WIDTH, FLOOR_HEIGHT);
	//Selección de textura
	switch (type) {
	case _PASTBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("PastFloor"));
		break;
	case _PRESENTBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("PresentFloor"));
		break;
	case _FUTUREBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("FutureFloor"));
		break;
	case _BOSSBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("BossFloor"));
		break;
	}

	//Creamos el jugador e informamos a la camara de que debe seguirle
	player = addGameObject<Player>(_grp_PLAYER);
	camera->startFollowObject(player);
}