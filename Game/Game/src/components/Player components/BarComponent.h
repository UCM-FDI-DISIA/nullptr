#pragma once

#include "../Card Components/CardComponent.h"
#include "../General Components/HeatlhComponent.h"

class BarComponent : public Component {
private:
	Transform* tr;
	int currentCuantity;
	bool isLifeBar;

public:
	static const int id = _BAR_COMPONENT;

	// Constructoras
	BarComponent(bool _isLifeBar, int _currentCuantity);
	
	// Inicializar componentes
	virtual void initComponent();

	// Cambios de barra
	void changeBar(int changeValue);
	void processManaChange(int cuantity);
	void processLifeChange(int cuantity);
};