#pragma once

#include "../../components/ecs.h"
#include "../../core/GameObject.h"
#include "../../components/Transform.h"
#include "../../components/Image.h"
#include "../../components/ButtonComponent.h"

class Button : public GameObject {
private:

public:
	Button() : GameObject() {
		addComponent<Transform>();
		addComponent<Image>();
		//addComponent<Animator>(_ANIMATOR);
		addComponent<ButtonComponent>();
	}
};