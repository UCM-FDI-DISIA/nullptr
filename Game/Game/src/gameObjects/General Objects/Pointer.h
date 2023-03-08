#pragma once
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General components/PointerComponent.h"
#include "../../components/General components/Image.h"

class Pointer : public GameObject {
private:
	Transform* followObjectTransform;
	Transform* transform;
	PointerComponent* pointerComponent;
public:
	// Constructora
	Pointer();

	// Establece el objeto a seguir
	inline void setFollowObject(GameObject* followObject_) {
		if (pointerComponent != nullptr) {
			pointerComponent->setFollowObject(followObject_);
			getComponent<Image>()->attachToCamera();
		}
	}

	// Establece el radio
	inline void setRadius(float radius_) {
		if (pointerComponent != nullptr) {
			pointerComponent->setRadius(radius_);
		}
	}

	// Devuelve el radio
	inline float getRadius() {
		if (pointerComponent != nullptr) {
			return pointerComponent->getRadius();
		}
	}
};