#include "CameraComponent.h"

// Constructora
CameraComponent::CameraComponent() : transform(nullptr), followObjectTransform(nullptr) {}

// Inicializa el componente
void CameraComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
}

// Setea el objeto a seguir
void CameraComponent::setFollowObject(GameObject* followObject_) {
	followObjectTransform = followObject_->getComponent<Transform>();
	followObjectInitialPosition = followObjectTransform->getInitialPosition();
}

// Sigue la posicion del followObject
void CameraComponent::update() {
	if (followObjectTransform != nullptr) {
		transform->setPos(followObjectInitialPosition - followObjectTransform->getPos());
	}
}