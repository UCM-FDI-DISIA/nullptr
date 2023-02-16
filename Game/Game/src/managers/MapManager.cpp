#include "MapManager.h"


MapManager::MapManager(SDLApplication* game) {
	Button* button1 = new Button(Pasado, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 1 * 30), "Pasado");
	Button* button2 = new Button(Presente, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Presente");
	Button* button3 = new Button(Futuro, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Futuro");
	Button* button4 = new Button(Tienda, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Tienda");
	Button* button5 = new Button(Cofre, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Cofre");


	addGameObject(button1);
	addGameObject(button2);
	addGameObject(button3);
	addGameObject(button4);
	addGameObject(button5);
}

void MapManager::Pasado(SDLApplication* game) {//para el pasado
	cout << "HE SIDO CLICADO Pasado" << endl;
	SDLApplication::newScene<PaBattleScene>(game);
}
void MapManager::Presente(SDLApplication* game) {//para el presente
	cout << "HE SIDO CLICADO Presente " << endl;
	SDLApplication::newScene<PreBattleScene>(game);
}
void MapManager::Futuro(SDLApplication* game) {//para el futuro
	cout << "HE SIDO CLICADO Futuro" << endl;
	SDLApplication::newScene<FuBattleScene>(game);
}
void MapManager::Tienda(SDLApplication* game) {//para la tienda
	cout << "HE SIDO CLICADO Tienda" << endl;
	SDLApplication::newScene<ShopScene>(game);
}
void MapManager::Cofre(SDLApplication* game) {//para el cofre
	cout << "HE SIDO CLICADO Cofre" << endl;
	SDLApplication::newScene<ChestScene>(game);
}