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

	AnimatorInfo(string _k) : key(_k), w(MM_BUTTON_WIDTH), h(MM_BUTTON_HEIGHT), fw(BUTTON_SPRITE_WIDTH), fh(BUTTON_SPRITE_HEIGHT), 
		rows(BUTTON_SPRITE_ROWS), cols(BUTTON_SPRITE_COLUMS) { }
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