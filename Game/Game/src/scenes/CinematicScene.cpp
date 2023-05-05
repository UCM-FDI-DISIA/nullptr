#include "CinematicScene.h"


CinematicScene::CinematicScene(string textureKey, int fw, int fh, int r, int c, Animation cinematic, CallBack onComplete) :
	onComplete_(onComplete){
	GameObject* go = addGameObject();
	go->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, sdlutils().width(), sdlutils().height());
	animator = go->addComponent<Animator>(&sdlutils().images().at(textureKey), fw, fh, r, c);
	animator->createAnim("cine", cinematic);
	animator->play("cine");
	if (textureKey == CINEMATIC_INITIAL_NAME) {
		cinematicMusic = &sdlutils().musics().at(INIT_MUSIC);
	}
	else if (textureKey == CINEMATIC_FINAL_NAME) {
		cinematicMusic = &sdlutils().musics().at(INIT_MUSIC);
	}

	createButton(QUIT_CINEMATIC_BUTTON_POS, QUIT_CINEMATICFRAME_BUTTON_POS, onComplete_, SKIP)->setAsDefaultButton();

	cinematicMusic->play();
}

void CinematicScene::update() {
	GameState::update();
	if (animator->animationComplete()) {
		onComplete_();
	}
}