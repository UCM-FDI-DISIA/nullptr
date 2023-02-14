#include "AlbumScene.h"
#include "../core/SDLApplication.h"

AlbumScene::AlbumScene(SDLApplication* _game) : GameState(_game) {
	cout << "Has entrado en la escena del album" << endl;
}