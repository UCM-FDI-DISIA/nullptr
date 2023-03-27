#pragma once

#include "GameState.h"

class SDLApplication;
class GameOverScene : public GameState {
private:
	SoundEffect* deathSound;
public:
	GameOverScene();
	virtual ~GameOverScene();
	
	// Crear un botón especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
};