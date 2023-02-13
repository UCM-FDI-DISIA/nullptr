#include "MapScene.h"
#include "../managers/MapManager.h"
#include "../core/SDLApplication.h"
#include "../managers/MainMenuManager.h"

MapScene::MapScene(SDLApplication* _game) : GameState(_game) {
	MapManager* msm = new MapManager(game);
	sceneManagers.push_back(msm);
}

