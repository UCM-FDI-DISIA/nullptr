#pragma once
#include "Component.h"
#include "Transform.h"
#include "../sdlutils/InputHandler.h"

enum State { OnOut = 0, OnOver, OnClick };

typedef void CallBack(Manager* game);

class ButtonComponent : public Component {

private:
	int state = 0;
	CallBack* function;
	Transform* transform;

public:
	ButtonComponent() : Component() {}

	virtual void update();
	virtual void handleInput();
};