#pragma once

#include "../Card Components/CardComponent.h"
#include "../General Components/HealthComponent.h"
#include <tuple>

// Tipos propios
using decs = int;
using cents = int;
using unids = int;

class BarComponent : public Component {
private:
	Transform* tr;
	int currentCuantity;

public:
	static const int id = _BAR_COMPONENT;

	// Constructoras
	BarComponent(int _currentCuantity = 0);
	
	// Inicializar componentes
	virtual void initComponent();

	// Métodos para cambios en las barras anteriores
	void onManaChanges(float value, float maxValue, vector<GameObject*>& myNumbers);
	void onHealthChanges(float value, float maxValue, vector<GameObject*>& myNumbers);
	void onEtherChanges(float value, vector<GameObject*>& myNumbers);
	void changeNumbers(vector<GameObject*>& vect, int value);
	void changeEtherNumbers(GameObject* num, int value);

	// Cálculos
	tuple<cents, decs, unids> getUnits(int value);
	float getFactored(float maxValue, float value);
	void changeAnimatorSrcRelativeWidth(GameObject* bar, float maxValue, float value);
	void changeAnimatorSrcRelativeHeight(GameObject* bar, float maxValue, float value);
};