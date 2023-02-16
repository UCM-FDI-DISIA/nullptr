#include "FuBattleScene.h"
#include "../core/SDLApplication.h"

// Constructora
FuBattleScene::FuBattleScene(SDLApplication* _game) : GameState(_game) {
  cout << "Has entrado en la escena de Batalla" << endl;

	// Quitar cuando se cree el mapa de combate
	floor = new GameObject();
	floor->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
	floor->addComponent<Image>(_game->getTexture("Player"), getCamera()->getComponent<Transform>());
	stateScene.push_back(floor);

	player = new Player(_game, getCamera());
	stateScene.push_back(player);

	Button* MainMenu = new Button(mainMenu, game, Vector2D(WIN_WIDTH / 2 - 79,10), "Opciones");
	stateScene.push_back(MainMenu);
}
void FuBattleScene::mainMenu(SDLApplication* _game) {
	SDLApplication::newScene<MainMenuScene>(_game);
}