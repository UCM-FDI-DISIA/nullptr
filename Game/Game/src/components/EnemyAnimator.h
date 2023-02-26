#pragma once
#ifndef ENEMY_ANIMATOR_H_
#define ENEMY_ANIMATOR_H_
#include "Animator.h"
#include "../core/GameObject.h"

class EnemyAnimator : public Animator {
private:
	Transform* transform;
public:
	// Identificador
	static const int id = _ENEMY_ANIMATOR;

	// Constructora
	EnemyAnimator(Texture* _texture, int _w, int _h, int _r, int _c) :
		Animator(_texture, _w, _h, _r, _c), transform(nullptr) {}

	// Destructora
	~EnemyAnimator();

	// Inicializa el componente
	virtual void initComponent();

	// Actualiza la animacion del Player dependiendo de su velocidad
	virtual void update();
};
#endif // !ENEMY_ANIMATOR_H_
