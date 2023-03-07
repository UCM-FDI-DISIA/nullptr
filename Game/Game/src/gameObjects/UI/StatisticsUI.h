#pragma once
#include "../../core/SDLApplication.h"
#include "../GameObject.h"
#include "../../components/Player components/BarComponent.h"

class StatisticsUI : public GameObject {
private:
	// Objeto
	GameObject* statistics;

	// Indicador de éter
	GameObject* etherMeter;
	// Barras de vida y maná
	GameObject* manaBar;
	GameObject* healthBar;

	float fullMana;
	float fullLife;

public:
	void initGameObject(int life, int mana);

	// Métodos virtuales
	virtual void render() const;
	virtual void update();

	void createLifeBar(int value);
	void createManaBar(int value);

	void OnManaChanges(float value);
	void OnHealthChanges(float value);
};