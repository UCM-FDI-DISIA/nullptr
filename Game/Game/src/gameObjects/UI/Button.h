#pragma once
#include "../../components/ecs.h"
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/General Components/ButtonComponent.h"
#include "../../components/General Components/Animator.h"
#include "../../data/constants.h"

class Button : public GameObject {
private:
	ButtonComponent* bComp;
public:
	// A�ade los componentes al bot�n y crea sus animaciones
	virtual void initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, GameObject* _frame);
	virtual void initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, int index = -1, GameObject* _frame = nullptr, float horizontalMult = 1.0f, float verticalMult = 1.0f);
	virtual void initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, Animation _onOutAnimation, Animation _onOverAnimation, Animation _onClickAnimation, int index = -1, GameObject* _frame = nullptr, float horizontalMult = 1.0f, float verticalMult = 1.0f);

	// Crear animaciones
	void createButtonAnimations(Animator* animator);
	void createButtonAnimations(Animator* animator, Animation onOut, Animation onOver, Animation onClick);

	void setAsDefaultButton();
	void setAsCurrentButton();
	bool isCurrentButton();

	inline void setCallBack(CallBack _cb) { if (bComp != nullptr) bComp->setCallBack(_cb); }
};