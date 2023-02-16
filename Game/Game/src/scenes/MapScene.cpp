#include "MapScene.h"
#include "../core/SDLApplication.h"

MapScene::MapScene(SDLApplication* game) : GameState(game) {

	Button* button1 = new Button(pasado, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 1 * 30), "Pasado", 186, 76, 1, 1);
	Button* button2 = new Button(presente, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Presente", 186, 76, 1, 1);
	Button* button3 = new Button(futuro, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Futuro", 186, 76, 1, 1);
	Button* button4 = new Button(tienda, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Tienda", 186, 76, 1, 1);
	Button* button5 = new Button(cofre, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Cofre", 186, 76, 1, 1);
	Button* button6 = new Button(salir, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 1 * 30), "SalirO", 186, 76, 1, 1);

	stateScene.push_back(button1);
	stateScene.push_back(button2);
	stateScene.push_back(button3);
	stateScene.push_back(button4);
	stateScene.push_back(button5);
	stateScene.push_back(button6);
}

void MapScene::pasado(SDLApplication* game) {//para el pasado
	cout << "HE SIDO CLICADO Pasado" << endl;
	SDLApplication::newScene<BattleScene>(game, 0);
}
void MapScene::presente(SDLApplication* game) {//para el presente
	cout << "HE SIDO CLICADO Presente " << endl;
	SDLApplication::newScene<BattleScene>(game, 1);
}
void MapScene::futuro(SDLApplication* game) {//para el futuro
	cout << "HE SIDO CLICADO Futuro" << endl;
	SDLApplication::newScene<BattleScene>(game, 2);
}
void MapScene::tienda(SDLApplication* game) {//para la tienda
	cout << "HE SIDO CLICADO Tienda" << endl;
	SDLApplication::newScene<ShopScene>(game);
}
void MapScene::cofre(SDLApplication* game) {//para el cofre
	cout << "HE SIDO CLICADO Cofre" << endl;
	SDLApplication::newScene<ChestScene>(game);
}
void MapScene::salir(SDLApplication* game) {//para el cofre
	cout << "HE SIDO CLICADO El menu inicial" << endl;
	SDLApplication::newScene<MainMenuScene>(game);
}