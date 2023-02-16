#pragma once

#include "../../components/ecs.h"
#include "../../core/GameObject.h"
#include "../../components/Transform.h"
#include "../../components/Image.h"
#include "../../components/ButtonComponent.h"
#include "../../components/Animator.h"

class SDLApplication;
typedef void CallBack(SDLApplication* game);
class Button : public GameObject {
private:

public:
	// Constructora
	Button(CallBack _cb, SDLApplication* game, Vector2D _pos, 
		string key, GameObject* _frame = nullptr, int _w = BUTTON_SPRITE_WIDTH, int _h = BUTTON_SPRITE_HEIGHT, int _r = BUTTON_SPRITE_ROWS, int _c = BUTTON_SPRITE_COLUMS);

	// Crear animaciones
	void createButtonAnimations(Animator* animator);
};