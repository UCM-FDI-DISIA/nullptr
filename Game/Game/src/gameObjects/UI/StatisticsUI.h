#pragma once
#include "../../core/SDLApplication.h"
#include "../GameObject.h"
#include "../../components/Player components/BarComponent.h"
#include <tuple>

// Tipos propios
using decs = int;
using cents = int;
using unids = int;

class StatisticsUI : public GameObject {
private:
	// Objeto
	GameObject* statistics;

	// Indicador de éter
	GameObject* etherMeter;
	// Barras de vida y maná
	GameObject* manaBar;
	GameObject* healthBar;

	// Contadores
	vector<GameObject*> lifeCounter;
	vector<GameObject*> manaCounter;

	float fullMana;
	float fullLife;

public:
	// Inicializar objeto
	void initGameObject(int life, int mana);

	// Métodos virtuales
	virtual void render() const;
	virtual void update();

	// Números de maná y vida
	void createNumberAnims(GameObject* obj, int value, int i);

	// Crear las barras de mana y de vida
	void createLifeBar(int value);
	void createManaBar(int value);

	// Métodos para cambios en las barras anteriores
	void OnManaChanges(float value);
	void OnHealthChanges(float value);
	void changeNumbers(vector<GameObject*> vect, int value);

	// Cálculos
	tuple<cents, decs, unids> getUnits(int value);
	void changeAnimatorSrcRelativeWidth(GameObject* bar, float maxValue, float value);
};