#pragma once
#include "../Component.h"
#include "../../gameObjects/GameObject.h"
#include "../Player components/BarComponent.h"
#include "Transform.h"
#include "../../core/GameControl.h"
#include <vector>

class ChargedPortalComponent : public Component {
private:
	// Números del contador y puntero al que se va a modificar
	vector<GameObject*>& numbers;
	GameObject* countDownNumber;

	// Componente de barra
	BarComponent* brComp;
	
	// Variables de control
	bool exit;
	double deltaTime;

	GameControl& gmCtrl_;

public:
	static const int id = _CHARGED_PORTAL;
	
	// Constructora
	ChargedPortalComponent(vector<GameObject*>& nums);

	// Métodos virtuales
	virtual void initComponent();
	virtual void update();

	// Métodos de activación
	void activateExit();
	void countDownSetup();
	//void countdown();
};