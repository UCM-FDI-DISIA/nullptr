#pragma once
#ifndef PLAYER_ANIMATOR_H_
#define PLAYER_ANIMATOR_H_
#include "Animator.h"
#include "../core/GameObject.h"

class PlayerAnimator : public Animator {
private:
	Transform* transform;
public:
	// Identificador
	static const int id = _PLAYER_ANIMATOR;
	// Constructora
	PlayerAnimator(Texture* _texture, int _w, int _h, int _r, int _c) : Animator(_texture, _w, _h, _r, _c), transform(nullptr) {}
	// Metodos esenciales
	virtual void initComponent();
	virtual void update();
};
#endif // !PLAYER_ANIMATOR_H_
