#pragma once

#include "GameState.h"
#include "../gameObjects/Node Objects/Map.h"

class MapScene : public GameState {
private:
	Button* exitButton;
	Transform* camTr;
	int camYLimit;
public:
	MapScene();

	void handleInput() override;

	// Mover la camara a la altura de los siguientes al current
	void moveCamera();

	// Creamos el enlace entre nodos
	void createConections(vector<vector<Node*>> const& nodes, vector<vector<Vector2D>> const& nodesPos, vector<int> const& nodesPerHeight, int alt);
};