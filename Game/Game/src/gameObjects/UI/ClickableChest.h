#pragma once
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/ButtonComponent.h"
#include "../../components/General Components/Animator.h"
#include "../../data/constants.h"



class ClickableChest : public GameObject {

private:
public:
	// Añade los componentes al botón y crea sus animaciones
	virtual void initGameObject(CallBack _cb, SDLApplication* game, Vector2D _pos, AnimatorInfo _animInfo);

	// Crear animaciones
	void createButtonAnimations(Animator* animator);


};