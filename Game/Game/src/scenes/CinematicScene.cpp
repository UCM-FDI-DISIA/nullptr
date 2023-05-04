#include "CinematicScene.h"


CinematicScene::CinematicScene(string textureKey, int fw, int fh, int r, int c, Animation cinematic, CallBack onComplete) :
	onComplete_(onComplete){
	GameObject* go = addGameObject();
	go->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, sdlutils().width(), sdlutils().height());
	animator = go->addComponent<Animator>(&sdlutils().images().at(textureKey), fw, fh, r, c);
	animator->createAnim("cine", cinematic);
	animator->play("cine");

	createButton(MS_EXIT_BUTTON_POS, MS_EXITFRAME_BUTTON_POS, onComplete_, SKIP)->setAsDefaultButton();
}

void CinematicScene::update() {
	GameState::update();
	if (animator->animationComplete()) {
		onComplete_();
	}
}