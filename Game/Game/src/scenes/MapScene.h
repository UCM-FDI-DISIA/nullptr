#pragma once

#include "GameState.h"
#include "../gameObjects/Node Objects/Map.h"
#include "../gameObjects/UI/Button.h"

class MapScene : public GameState {
public:
	MapScene();

	// Crear un botón especificado en la escena
	Button* createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);

	// Mover la camara a la altura de los siguientes al current
	void moveCamera();

	// Creamos el enlace entre nodos
	void createConections(vector<vector<Node*>> const& nodes, vector<vector<Vector2D>> const& nodesPos, vector<int> const& nodesPerHeight, int alt);
};