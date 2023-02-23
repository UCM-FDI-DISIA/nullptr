#pragma once
#include "../../components/ecs.h"
#include "../../core/GameObject.h"
#include "../../components/Transform.h"
#include "../../components/Image.h"
#include "../../components/ButtonComponent.h"
#include "../../components/Animator.h"

class SDLApplication;
typedef void CallBack(); // cleon says: igual esto tendría que estar en un .h genérico o algo así? quién sabe.
class Button : public GameObject {
private:
public:
	// Añade los componentes al botón y crea sus animaciones
	// // cleon says:  11 parámetros == 11 gatitos que sufren
	virtual void initGameObject(CallBack* _cb, SDLApplication* game, Vector2D _pos, string key, int _w, int _h, int _fw, int _fh, int _r, int _c, GameObject* _frame = nullptr);

	// Crear animaciones
	void createButtonAnimations(Animator* animator);
};