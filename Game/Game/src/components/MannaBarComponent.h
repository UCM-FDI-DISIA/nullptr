#pragma once

#include "CardComponent.h"

class MannaBarComponent : public Component {
private:
	CardComponent* info;
	Transform* tr;
	int currentManna;
public:
	static const int id = _MANA_BAR_COMPONENT;
	MannaBarComponent(CardComponent* _info);
	
	virtual void initComponent();
	void changeBar();
};