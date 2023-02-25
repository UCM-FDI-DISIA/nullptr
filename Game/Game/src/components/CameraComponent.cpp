#include "CameraComponent.h"

/*
	Se encarga de actualizar la posicion de la camara dependiendo del transform del objeto a seguir.
*/

// Destructora
CameraComponent::~CameraComponent() {
	transform = nullptr;
	followObjectTransform = nullptr;
}

// Inicializa el componente
void CameraComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
}

// Sigue la posicion del followObject
void CameraComponent::update() {
	if (followObjectTransform != nullptr) {
		transform->setPos(followObjectInitialPosition - followObjectTransform->getPos());
	}
}

// Setea el objeto a seguir
void CameraComponent::setFollowObject(GameObject* followObject_) {
	followObjectTransform = followObject_->getComponent<Transform>();
	if (followObjectTransform != nullptr) {
		followObjectInitialPosition = followObjectTransform->getInitialPosition();
	}
}