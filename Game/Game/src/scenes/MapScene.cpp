#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../node/Node.h"

MapScene::MapScene(SDLApplication* game) : GameState(game), nodeMap(Node::getNodeMap()) {
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
	for (Node* node : nodeMap) {
		addGameObject<Button>(node->loadNode(), game, node->getPosition(), node->getTextureKey(), NODE_WIDTH, NODE_HEIGHT, 186, 76, 1, 1);
	}
}

void MapScene::pasado(SDLApplication* game) {//para el pasado
	cout << "HE SIDO CLICADO Pasado" << endl;
	SDLApplication::newScene<BattleScene>(game, 0);
}
void MapScene::presente(SDLApplication* game) {//para el presente
	cout << "HE SIDO CLICADO Presente " << endl;
	SDLApplication::newScene<BattleScene>(game, 1);
}
void MapScene::futuro(SDLApplication* game) {//para el futuro
	cout << "HE SIDO CLICADO Futuro" << endl;
	SDLApplication::newScene<BattleScene>(game, 2);
}
void MapScene::tienda(SDLApplication* game) {//para la tienda
	cout << "HE SIDO CLICADO Tienda" << endl;
	SDLApplication::newScene<ShopScene>(game);
}
void MapScene::cofre(SDLApplication* game) {//para el cofre
	cout << "HE SIDO CLICADO Cofre" << endl;
	SDLApplication::newScene<ChestScene>(game);
}
void MapScene::salir(SDLApplication* game) {//para el cofre
	cout << "HE SIDO CLICADO El menu inicial" << endl;
	SDLApplication::newScene<MainMenuScene>(game);
}