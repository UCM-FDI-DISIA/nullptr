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
		transform->setPos(cameraInitialPosition - followObjectTransform->getPos());
	}
}

// Setea el objeto a seguir
void CameraComponent::setFollowObject(GameObject* followObject_) {
	followObjectTransform = followObject_->getComponent<Transform>();
	if (followObjectTransform != nullptr) {
		cameraInitialPosition = Vector2D(WIN_WIDTH / 2 - followObjectTransform->getWidth() / 2, WIN_HEIGHT / 2 - followObjectTransform->getHeight()/2);
	}
}