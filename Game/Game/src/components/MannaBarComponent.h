#pragma once

#include "CardComponent.h"

class MannaBarComponent : public Component {
private:
	CardComponent* info;
	Transform* tr;
	int currentManna;
public:
	static const int id = _MANA_BAR_COMPONENT;
	MannaBarComponent();
	
	virtual void initComponent();
	virtual void update();
};