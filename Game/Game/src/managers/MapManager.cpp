#include "MapManager.h"
#include "../gameObjects/UI/Button.h"
#include "../core/SDLApplication.h"

MapManager::MapManager(SDLApplication* game) {
	
	
		Button* button1 = new Button(Test1, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 1 * 30), "Pasado");
		addGameObject(button1);
		Button* button2 = new Button(Test2, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 2 * 30), "Presente");
		addGameObject(button2);
		Button* button3 = new Button(Test3, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Futuro");
		addGameObject(button3);
}

void MapManager::Test1(SDLApplication* game) {
	cout << "HE SIDO CLICADO 1" << endl;
}
void MapManager::Test2(SDLApplication* game) {
	cout << "HE SIDO CLICADO 2" << endl;
}
void MapManager::Test3(SDLApplication* game) {
	cout << "HE SIDO CLICADO 3" << endl;
}