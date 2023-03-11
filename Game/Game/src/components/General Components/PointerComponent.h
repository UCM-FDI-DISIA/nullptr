#pragma once
#include "../Component.h"
#include "../../gameObjects/GameObject.h"
#include "../General Components/Transform.h"
#include <cassert>

class PointerComponent : public Component {
private:
	GameState* gStt;
	Transform* pointerTransform;
	Transform* followObjectTransform;
	float radius;
public:
	// Identificador
	static const int id = _POINTERCOMPONENT;
	// Constructora
	PointerComponent(GameState* gStt_);
	// Inicializa el componente
	void initComponent();
	// Actualiza la posicion del puntero dependiendo de la posicion del cursor
	void update();
	// Devuelve la posicion del cursor
	inline Vector2D getMousePos() {
		int x, y;
		SDL_GetMouseState(&x, &y);
		return Vector2D(x, y);
	}
	// Establece el objeto a seguir
	inline void setFollowObject(GameObject* followObject_) {
		followObjectTransform = followObject_->getComponent<Transform>();
	}
	// Establece el radio
	inline void setRadius(float radius_) {
		radius = radius_;
	}
	// Devuelve el radio
	inline float getRadius() {
		return radius;
	}
};