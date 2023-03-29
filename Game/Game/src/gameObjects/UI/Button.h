#pragma once
#include "../../components/ecs.h"
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/ButtonComponent.h"
#include "../../components/General Components/Animator.h"
#include "../../data/constants.h"



class Button : public GameObject {

public:
	// A�ade los componentes al bot�n y crea sus animaciones
	virtual void initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, GameObject* _frame);
	virtual void initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, int index = -1, GameObject* _frame = nullptr);
	
	// Crear animaciones
	void createButtonAnimations(Animator* animator);
};