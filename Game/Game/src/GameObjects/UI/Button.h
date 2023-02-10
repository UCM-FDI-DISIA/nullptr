#pragma once

#include "../../components/ecs.h"
#include "../../core/GameObject.h"
#include "../../components/Transform.h"


class Button : public GameObject {
private:

public:
	Button() : GameObject() {
		addComponent<Transform>(_TRANSFORM);
		//addComponent<Image>(_IMAGE);
		//addComponent<Animator>(_ANIMATOR);
		//addComponent<ButtonComponent>(_INTERACTIVE);
	}
};