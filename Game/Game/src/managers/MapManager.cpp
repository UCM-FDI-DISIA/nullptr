#include "MapManager.h"
#include "../gameObjects/UI/Button.h"
#include "../core/SDLApplication.h"

MapManager::MapManager(SDLApplication* game) {

	Button* button1 = new Button(Test1, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 1 * 30), "Pasado");
	Button* button2 = new Button(Test2, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Presente");
	Button* button3 = new Button(Test3, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Futuro");
	Button* button4 = new Button(Test4, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Tienda");
	Button* button5 = new Button(Test5, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Cofre");


	addGameObject(button1);
	addGameObject(button2);
	addGameObject(button3);
	addGameObject(button4);
	addGameObject(button5);
}

void MapManager::Test1(SDLApplication* game) {//para el pasado
	cout << "HE SIDO CLICADO Pasado" << endl;
	SDLApplication::newScene<BattleScene>(game);
}
void MapManager::Test2(SDLApplication* game) {//para el presente
	cout << "HE SIDO CLICADO Presente " << endl;
	SDLApplication::newScene<BattleScene>(game);
}
void MapManager::Test3(SDLApplication* game) {//para el futuro
	cout << "HE SIDO CLICADO Futuro" << endl;
	SDLApplication::newScene<BattleScene>(game);
}
void MapManager::Test4(SDLApplication* game) {//para la tienda
	cout << "HE SIDO CLICADO Tienda" << endl;
	SDLApplication::newScene<ShopScene>(game);
}
void MapManager::Test5(SDLApplication* game) {//para el cofre
	cout << "HE SIDO CLICADO Cofre" << endl;
	SDLApplication::newScene<ChestScene>(game);
}