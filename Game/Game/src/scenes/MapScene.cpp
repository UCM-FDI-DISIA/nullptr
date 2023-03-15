#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/Node Objects/NodeButton.h"

MapScene::MapScene() {
	vector<vector<Node*>> const& nodeMap = map().getNodeMap();
	vector<int> const& nodesPerHeight = map().getNodesPerWidth();
	int i = 0;
	for (auto& height : nodeMap) {
		int j = 0;
		for (Node* node : height) {
			if (node != nullptr) { 
				switch (nodesPerHeight[i]) {
				case 1:
					addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[2], WIN_HEIGHT - 50 - NODE_POSITION_Y * i));
					break;
				case 2:
					if (j == 0) addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[1], WIN_HEIGHT - 50 - NODE_POSITION_Y * i));
					else addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[3], WIN_HEIGHT - 50 - NODE_POSITION_Y * i));
					break;
				case 3:
					if (j == 0) addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[0], WIN_HEIGHT - 50 - NODE_POSITION_Y * i));
					else if (j == 1) addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[2], WIN_HEIGHT - 50 - NODE_POSITION_Y * i));
					else addGameObject<NodeButton>(node, node->loadNode(), Vector2D(NODE_POSITIONS_X[4], WIN_HEIGHT - 50 - NODE_POSITION_Y * i));
					break;
				}

				++j;
			}
		}
		++i;
	}
}