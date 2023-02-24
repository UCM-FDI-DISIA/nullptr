#pragma once
#include "../../components/ecs.h"
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/ButtonComponent.h"
#include "../../components/General Components/Animator.h"

class Button : public GameObject {
private:
public:
	// Añade los componentes al botón y crea sus animaciones
	// // cleon says:  11 parámetros == 11 gatitos que sufren
	virtual void initGameObject(CallBack _cb, SDLApplication* game, Vector2D _pos, string key, int _w, int _h, int _fw, int _fh, int _r, int _c, GameObject* _frame = nullptr);

	// Crear animaciones
	void createButtonAnimations(Animator* animator);
};