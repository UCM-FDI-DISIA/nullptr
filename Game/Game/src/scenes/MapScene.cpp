#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/NodeButton.h"

MapScene::MapScene() : GameState(), nodeMap(Node::getNodeMap()) {
	/*addGameObject<Button>(pasado, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 1 * 30), "Pasado", 186, 76, 1, 1);
	addGameObject<Button>(presente, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Presente", 186, 76, 1, 1);
	addGameObject<Button>(futuro, game, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Futuro", 186, 76, 1, 1);
	addGameObject<Button>(tienda, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 3 * 30), "Tienda", 186, 76, 1, 1);
	addGameObject<Button>(cofre, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 5 * 30), "Cofre", 186, 76, 1, 1);
	addGameObject<Button>(salir, game, Vector2D(WIN_WIDTH / 2 - 300, (WIN_HEIGHT / 2 - 30) + 1 * 30), "SalirO", 186, 76, 1, 1);

	for (Node* node : nodeMap) {
		addGameObject<Button>(node->loadNode(), game, Vector2D(WIN_WIDTH/2, WIN_HEIGHT/2), node->getTextureKey(), 186, 76, 1, 1);
	}*/

	/*for (int i = 0; i < nodeMap.size(); ++i) {
		addGameObject<Button>(nodeMap[i]->loadNode(), game, nodeMap[i]->getPosition(), nodeMap[i]->getTextureKey(), 186, 76, 1, 1);
	}*/
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