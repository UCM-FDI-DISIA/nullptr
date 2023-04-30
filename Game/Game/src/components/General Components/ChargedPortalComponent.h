#pragma once
#include "../Component.h"
#include "../../gameObjects/GameObject.h"
#include "../Player components/BarComponent.h"
#include "Transform.h"
#include "../../core/GameControl.h"
#include <vector>
#include "../../scenes/BattleScene.h"


class ChargedPortalComponent : public Component {
private:
	// Números del contador y puntero al que se va a modificar
	vector<GameObject*>& numbers;
	GameObject* countDownNumber;
	BattleScene* scene;
	// Componente de barra
	BarComponent* brComp;
	
	// Variables de control
	bool exit;
	double deltaTime;

	GameControl& gmCtrl_;

public:
	static const int id = _CHARGED_PORTAL;
	
	// Constructora
	ChargedPortalComponent(vector<GameObject*>& nums, GameState* scen);

	// Métodos virtuales
	virtual void initComponent();
	virtual void update();

	// Métodos de activación
	void activateExit();
	void countDownSetup();
	//void countdown();
};