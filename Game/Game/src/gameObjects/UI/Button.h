#pragma once
#include "../../components/ecs.h"
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/ButtonComponent.h"
#include "../../components/General Components/Animator.h"

struct AnimatorInfo {
	string key;
	int w, h;
	int fw, fh;
	int rows, cols;
	//Con constantes para botones genéricos
	AnimatorInfo(string _k) : key(_k), w(MM_BUTTON_WIDTH), h(MM_BUTTON_HEIGHT), fw(BUTTON_SPRITE_WIDTH), fh(BUTTON_SPRITE_HEIGHT), 
		rows(BUTTON_SPRITE_ROWS), cols(BUTTON_SPRITE_COLUMS) { }
	//Con parámetros específicos
	AnimatorInfo (string _k, int _w, int _h, int _fw = BUTTON_SPRITE_WIDTH, int _fh = BUTTON_SPRITE_HEIGHT,
		int _r = BUTTON_SPRITE_ROWS, int _c = BUTTON_SPRITE_COLUMS) : 
		key(_k), w(_w), h(_h), fw(_fw), fh(_fh), rows(_r), cols(_c) { }
};

class Button : public GameObject {
private:
public:
	// Añade los componentes al botón y crea sus animaciones
	virtual void initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, GameObject* _frame = nullptr);

	// Crear animaciones
	void createButtonAnimations(Animator* animator);
};