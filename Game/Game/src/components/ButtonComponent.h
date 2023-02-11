#pragma once
#include "Component.h"
#include "Transform.h"
#include "../sdlutils/InputHandler.h"

enum State { OnOut = 0, OnOver, OnClick };

typedef void CallBack(Manager* game);

class ButtonComponent : public Component {

private:
	int state;
	CallBack* function;
	Transform* tr;

public:
	static const int id = _BUTTON;
	ButtonComponent(CallBack* _f) : Component(), state(0), function(_f) {}

	virtual void update();
	virtual void handleInput();
	virtual void initComponent();
};