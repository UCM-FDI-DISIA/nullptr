#pragma once
#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "GameState.h"
#include "../components/General Components/Transform.h"
#include "../components/General Components/Image.h"
#include "../components/General Components/Animator.h"

//struct AnimatorInfo {
//	string key;
//	int w, h;
//	int fw, fh;
//	int rows, cols;
//
//	AnimatorInfo(string _k, int _w, int _h, int _fw, int _fh, int _r, int _c) : 
//		key(_k), w(_w), h(_h), fw(_fw), fh(_fh), rows(_r), cols(_c) { }
//};

class MainMenuScene : public GameState {
private:
public:
	// Constructora
	MainMenuScene();

	// Crear un botón especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
};

#endif