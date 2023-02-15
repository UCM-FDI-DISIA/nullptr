#include "MainMenuScene.h"
#include "../core/SDLApplication.h"
#include "../GameObjects/UI/Button.h"

MainMenuScene::MainMenuScene(SDLApplication* _game) : GameState(_game) {
	//Imagen de fondo
	GameObject* background = new GameObject();
	background->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 800, 600);
	background->addComponent<Image>(game->getTexture("MainMenuFondo"));
	stateScene.push_back(background);

	//Marco de los botones
	for (int i = 0; i < 4; i++) {
		GameObject* marco = new GameObject();
		marco->addComponent<Transform>(Vector2D(WIN_WIDTH/ 2 - 103, (WIN_HEIGHT * (4 + i) / 8) - 44), Vector2D(0, 0), 190, 90);
		Animator* anim = marco->addComponent<Animator>(game->getTexture("Marco"), 95, 45, 5, 2);
		anim->createAnim("Idle", 0, 9, 5, -1);
		stateScene.push_back(marco);
	}
	
	// Botón jugar
	Button* Play = new Button(play, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT / 2), "Jugar", 79, 18, 6, 2);
	createButtonAnimations(Play->getComponent<Animator>());
	stateScene.push_back(Play);

	// Botón opciones
	Button* Options = new Button(options, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 5 / 8), "Opciones", 79, 18, 6, 2);
	createButtonAnimations(Options->getComponent<Animator>());
	stateScene.push_back(Options);

	// Botón album
	Button* Album = new Button(album, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 6 / 8), "Salir", 79, 18, 6, 2);
	createButtonAnimations(Album->getComponent<Animator>());
	stateScene.push_back(Album);

	// Botón salir
	Button* Exit = new Button(exit, game, Vector2D(WIN_WIDTH / 2 - 79, WIN_HEIGHT * 7 / 8), "Salir", 79, 18, 6, 2);
	createButtonAnimations(Exit->getComponent<Animator>());
	stateScene.push_back(Exit);
}

void MainMenuScene::play(SDLApplication* game) {
	SDLApplication::newScene<BattleScene>(game);
}

void MainMenuScene::options(SDLApplication* game) {
	SDLApplication::newScene<OptionsMenuScene>(game);
}

void MainMenuScene::album(SDLApplication* game) {
	SDLApplication::newScene<AlbumScene>(game);
}

void MainMenuScene::exit(SDLApplication* game) {
	game->quitGame(game);
}

void MainMenuScene::createButtonAnimations(Animator* animator) {
	animator->createAnim("OnClick", 11, 11, 1, -1);
	animator->createAnim("OnOver", 0, 9, 5, -1);
	animator->createAnim("Idle", 10, 10, 1, -1);
	animator->play("Idle");
}