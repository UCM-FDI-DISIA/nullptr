#pragma once
#include "Component.h"
#include "Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Animator.h"

enum State { OnOut = 0, OnOver, OnClick };

class SDLApplication;
typedef void CallBack(SDLApplication* game);

class ButtonComponent : public Component {

private:
	SDLApplication* game;
	int state;
	CallBack* function;
	Transform* tr;
	Animator* anim;

public:
	static const int id = _BUTTON;
	ButtonComponent(CallBack* _f, SDLApplication* _g) : Component(), state(0), function(_f), game(_g) {}

	virtual void update();
	virtual void handleInput();
	virtual void initComponent();
};