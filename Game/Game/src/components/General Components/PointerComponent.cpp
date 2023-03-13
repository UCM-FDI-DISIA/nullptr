#include "PointerComponent.h"
#include "../../scenes/GameState.h"

// Constructora
PointerComponent::PointerComponent(GameState* gStt_) : gStt(gStt_), pointerTransform(nullptr), followObjectTransform(nullptr), radius(POINTER_DEFAULT_RADIUS) {}

// Inicializa el componente
void PointerComponent::initComponent() {
	pointerTransform = gObj->getComponent<Transform>();
	assert(pointerTransform != nullptr);
}

// Actualiza la posicion del puntero dependiendo de la posicion del cursor
void PointerComponent::update() {
	// Si tiene objeto a seguir
	if (followObjectTransform != nullptr) {
		float posX = (float)(getMousePos().getX() - (followObjectTransform->getPos().getX() + followObjectTransform->getWidth() / 2 + gStt->getCamera()->getOffset().getX()));
		float posY = (float)(getMousePos().getY() - (followObjectTransform->getPos().getY() + followObjectTransform->getHeight() / 2 + gStt->getCamera()->getOffset().getY()));

		// Calculo de la posicion del puntero
		Vector2D dir = Vector2D(posX, posY).normalize() * radius;
		Vector2D followObjectCenterPosition = Vector2D(followObjectTransform->getPos().getX() + followObjectTransform->getWidth() / 2, followObjectTransform->getPos().getY() + followObjectTransform->getHeight() / 2);
		Vector2D pointerPosition = dir + followObjectCenterPosition - Vector2D(POINTER_WIDTH / 2, POINTER_HEIGHT / 2) + followObjectTransform->getInitialPosition() - followObjectTransform->getPos();

		// Calculo de la rotacion del puntero
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

		// Posicion
		pointerTransform->setPos(pointerPosition);
		// Rotacion
		pointerTransform->setRotation(angle);
	}
	// Si no tiene objeto a seguir funciona como cursor normal
	else {
		// Rotacion
		pointerTransform->setRotation(POINTER_NORMAL_INCLINATION);
		pointerTransform->setPos(getMousePos() + Vector2D(POINTER_HEIGHT / 2 * tan(POINTER_NORMAL_INCLINATION), 0));
	}
}