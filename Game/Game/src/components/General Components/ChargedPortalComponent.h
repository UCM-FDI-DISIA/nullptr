#pragma once
#include "../Component.h"
#include "../../gameObjects/GameObject.h"
#include "../Player components/BarComponent.h"
#include "Transform.h"
#include "../../core/GameControl.h"
#include <vector>

class ChargedPortalComponent : public Component {
private:
	// N�meros del contador y puntero al que se va a modificar
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

	// M�todos virtuales
	virtual void initComponent();
	virtual void update();

	// M�todos de activaci�n
	void activateExit();
	void countDownSetup();
	//void countdown();
};