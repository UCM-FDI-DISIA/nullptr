#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/NodeButton.h"

MapScene::MapScene() : GameState(), nodeMap(Node::getNodeMap()) {
	for (vector<Node*>::const_iterator node = nodeMap.begin(); node != nodeMap.end(); ++node) {
		addGameObject<NodeButton>(node, (*node)->loadNode());
	}
}

// Abre la escena de batalla en el pasado
void MapScene::pasado() {
	//SDLApplication::newScene<BattleScene>(0);
}
// Abre la escena de batalla en el presente
void MapScene::presente() {
	//SDLApplication::newScene<BattleScene>(1);
}
// Abre la escena de batalla en el furuto
void MapScene::futuro() {
	//SDLApplication::newScene<BattleScene>(2);
}
// Abre la escena de tienda
void MapScene::tienda() {
	SDLApplication::newScene<ShopScene>();
}
// Abre la escena de cofre
void MapScene::cofre() {
	SDLApplication::newScene<ChestScene>();
}
// Vuelve a la escena de menú principal
void MapScene::salir() {
	SDLApplication::newScene<MainMenuScene>();
}