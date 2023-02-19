#pragma once
#ifndef NODEBUTTONCOMPONENT_H_
#define NODEBUTTONCOMPONENT_H_

#include "ButtonComponent.h"
#include "../node/BattleNode.h"

class NodeButtonComponent : public ButtonComponent {
private:
	list<battleType>::iterator* it;
public:
	NodeButtonComponent(list<battleType>::iterator* _it, CallBack* _f, SDLApplication* _g, GameObject* _frame = nullptr) :
	ButtonComponent(_f, _g, _frame), it(_it) {}

	virtual void onClick() {
		BattleNode::lastType = it;
		ButtonComponent::onClick();
	}
};

#endif // !NODEBUTTONCOMPONENT_H_
