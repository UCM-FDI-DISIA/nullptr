#include "PointerComponent.h"

// Constructora
PointerComponent::PointerComponent() : pointerTransform(nullptr), followObjectTransform(nullptr), radius(POINTER_DEFAULT_RADIUS) {}

// Inicializa el componente
void PointerComponent::initComponent() {
	pointerTransform = gObj->getComponent<Transform>();
	assert(pointerTransform != nullptr);
}

// Actualiza la posicion del puntero dependiendo de la posicion del cursor
void PointerComponent::update() {
	// Si tiene objeto a seguir
	if (followObjectTransform != nullptr) {
		// Posicion
		Vector2D dir = (getMousePos() - followObjectTransform->getPos()).normalize() * radius;
		Vector2D followObjectCenterPosition = Vector2D(followObjectTransform->getPos().getX() + followObjectTransform->getWidth()/2, followObjectTransform->getPos().getY() + followObjectTransform->getHeight()/2);
		Vector2D pointerPosition = dir + followObjectCenterPosition - Vector2D(POINTER_WIDTH / 2, POINTER_HEIGHT / 2) + followObjectTransform->getInitialPosition() - followObjectTransform->getPos();
		pointerTransform->setPos(pointerPosition);

		// Rotacion
		float posX = (float)(getMousePos().getX() - (followObjectTransform->getPos().getX() + followObjectTransform->getWidth() / 2));
		float posY = (float)(getMousePos().getY() - (followObjectTransform->getPos().getY() + followObjectTransform->getHeight() / 2));
		float angle = abs(atan(posX / posY)) * 180 / M_PI;

		// Segundo cuadrante
		if (posX < 0 && posY < 0) {
			angle *= -1;
		}
		// Tercer cuadrante
		else if (posX < 0 && posY > 0) {
			angle += 180;
		}
		// Cuarto cuadrante
		else if (posX > 0 && posY > 0) {
			angle = 180 - angle;
		}

		pointerTransform->setRotation(angle);
	}
	// Si no tiene objeto a seguir funciona como cursor normal
	else {
		pointerTransform->setPos(getMousePos() - Vector2D(POINTER_WIDTH/2, 0));
	}
}