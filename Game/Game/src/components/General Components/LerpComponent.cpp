#include "LerpComponent.h"
#include "../../gameObjects/GameObject.h"
#include <cmath>

// Constructora
LerpComponent::LerpComponent(Transform* followObjectTransform_) : followObjectTransform(followObjectTransform_) {}

// Inicializa el component
void LerpComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
	assert(transform != nullptr);
}

// Actualiza su posicion
void LerpComponent::update() {
	if (followObjectTransform != nullptr) {
		Vector2D diff = (followObjectTransform->getCenter() - transform->getCenter());
		Vector2D normalizedDir = diff.normalize();
		if (diff.magnitude() > POINTER_DEFAULT_RADIUS * 2.3) 
			transform->setVel(normalizedDir * (PLAYER_SPEED + 20) * 2.1);
		else if (diff.magnitude() < POINTER_DEFAULT_RADIUS * 2.1) 
			transform->setVel(normalizedDir * -2.1 * (PLAYER_SPEED + 20));
		else if (diff.magnitude() <= POINTER_DEFAULT_RADIUS * 2.3 &&
			diff.magnitude() >= POINTER_DEFAULT_RADIUS * 2.1) transform->setVel(Vector2D());
	}
}