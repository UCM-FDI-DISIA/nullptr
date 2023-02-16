#include "MapScene.h"
#include "../core/SDLApplication.h"



MapScene::MapScene(SDLApplication* _game) : GameState(_game) {
	MapManager* msm = new MapManager(game);
	sceneManagers.push_back(msm);
}