#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/NodeButton.h"

MapScene::MapScene() : GameState(), nodeMap(Node::getNodeMap()) {
	for (vector<Node*>::const_iterator node = nodeMap.begin(); node != nodeMap.end(); ++node) {
		addGameObject<NodeButton>(node, (*node)->loadNode());
	}
}

// Abre la escena de shop
void MapScene::shop() {
	SDLApplication::newScene<ShopScene>();
}
// Abre la escena de chest
void MapScene::chest() {
	SDLApplication::newScene<ChestScene>();
}
// Vuelve a la escena de menú principal
void MapScene::exit() {
	SDLApplication::newScene<MainMenuScene>();
}