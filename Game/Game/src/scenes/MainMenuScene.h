#pragma once
#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Animator.h"

class MainMenuScene : public GameState {
private:
public:
	// Constructora
	MainMenuScene();

	// Crear un botón especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
};

#endif