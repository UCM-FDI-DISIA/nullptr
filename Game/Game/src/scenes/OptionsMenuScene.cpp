#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"

OptionsMenuScene::OptionsMenuScene() : GameState() {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), Constant::getInt("WIN_WIDTH"), Constant::getInt("WIN_HEIGHT"));
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground"));

	// Botones
	AnimatorInfo aI = AnimatorInfo(Constant::getString("EXIT"));
	addGameObject<Button>([]() { SDLApplication::newScene<MainMenuScene>(); }, Vector2D(Constant::getInt("WIN_WIDTH") / 2 - 79, (Constant::getInt("WIN_HEIGHT") / 4) + 50), aI);
	aI.key = Constant::getString("OPTIONS");
	addGameObject<Button>([]() { sdlutils().toggleFullScreen(); }, Vector2D(Constant::getInt("WIN_WIDTH") / 2 - 79, (Constant::getInt("WIN_HEIGHT") / 4) + 200), aI);
}