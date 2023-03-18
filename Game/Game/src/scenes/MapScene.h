#pragma once

#include "GameState.h"
#include "../gameObjects/Node Objects/Map.h"

class MapScene : public GameState {
public:
	MapScene();

	// Crear un botón especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);

	// Mover la camara a la altura de los siguientes al current
	void moveCamera();
};