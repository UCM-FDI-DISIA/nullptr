#include "MapScene.h"
#include "../core/SDLApplication.h"

MapScene::MapScene() : GameState() {
	addGameObject<Button>(pasado, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 1 * 30), "Pasado", 200, 76, 1, 1);
	addGameObject<Button>(presente, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Presente", 186, 76, 1, 1);
	addGameObject<Button>(futuro, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Futuro", 186, 76, 1, 1);
	addGameObject<Button>(tienda, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Tienda", 186, 76, 1, 1);
	addGameObject<Button>(cofre, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Cofre", 186, 76, 1, 1);
	addGameObject<Button>(salir, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 1 * 30), "SalirO", 186, 76, 1, 1);
}

void MapScene::pasado() {//para el pasado
	cout << "HE SIDO CLICADO Pasado" << endl;
	SDLApplication::newScene<BattleScene>(0);
}
void MapScene::presente() {//para el presente
	cout << "HE SIDO CLICADO Presente " << endl;
	SDLApplication::newScene<BattleScene>(1);
}
void MapScene::futuro() {//para el futuro
	cout << "HE SIDO CLICADO Futuro" << endl;
	SDLApplication::newScene<BattleScene>(2);
}
void MapScene::tienda() {//para la tienda
	cout << "HE SIDO CLICADO Tienda" << endl;
	SDLApplication::newScene<ShopScene>();
}
void MapScene::cofre() {//para el cofre
	cout << "HE SIDO CLICADO Cofre" << endl;
	SDLApplication::newScene<ChestScene>();
}
void MapScene::salir() {//para el cofre
	cout << "HE SIDO CLICADO El menu inicial" << endl;
	SDLApplication::newScene<MainMenuScene>();
}