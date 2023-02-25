#pragma once
#include "../../components/ecs.h"
#include "../../core/GameObject.h"
#include "../../components/Transform.h"
#include "../../components/Image.h"
#include "../../components/ButtonComponent.h"
#include "../../components/Animator.h"

struct AnimatorInfo {
	string key;
	int w, h;
	int fw, fh;
	int rows, cols;

	AnimatorInfo(string _k, int _w, int _h, int _fw, int _fh, int _r, int _c) :
		key(_k), w(_w), h(_h), fw(_fw), fh(_fh), rows(_r), cols(_c) { }
};

class Button : public GameObject {
private:
public:
	// Añade los componentes al botón y crea sus animaciones
	// // cleon says:  11 parámetros == 11 gatitos que sufren
	virtual void initGameObject(CallBack _cb, SDLApplication* game, Vector2D _pos, AnimatorInfo _animInfo, GameObject* _frame = nullptr);

	// Crear animaciones
	void createButtonAnimations(Animator* animator);
};