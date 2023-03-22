#pragma once
#include "GameState.h"
#include <vector>

class InventoryScene : public GameState {
private:
	
public:
	InventoryScene();

	// Crear un botón especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
};

// ola