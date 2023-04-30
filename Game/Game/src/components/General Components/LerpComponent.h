#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"

class LerpComponent : public Component {
private:
	Transform* transform;
	Transform* followObjectTransform;
	Vector2D followObjectInitialPosition;

public:
	// Identificador
	static const int id = _LERP_COMPONENT;

	// Constructora
	LerpComponent(Transform* followObjectTransform_);

	// Inicializa el component
	virtual void initComponent();

	// Actualiza su posicion
	void update();

	// Devuelve la posicion tras la interpolacion
	inline Vector2D lerp(Vector2D a, Vector2D b, float t) { return a + (b - a) * t; }
};