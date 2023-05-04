#include "TargetedComponent.h"
#include "../../gameObjects/GameObject.h"
#include "../../core/SDLApplication.h"

TargetedComponent::TargetedComponent(Transform* p, Transform* b) : 
	Component(), tr(nullptr), pltr(p), bossTr(b), state(Elongate), timeOffset(0), maxWidth(TARGETED_TENTACLE_MAX_W) { }

void TargetedComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
}

void TargetedComponent::update() {
	Vector2D dir;
	switch (state) {
		// Primer estado: alargar el objeto
		case Elongate:
			calculatePos();
			timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
			if (timeOffset >= 0.1) {
				tr->setWidth(tr->getWidth() + 10);
				timeOffset = 0;
			}

			if (tr->getWidth() >= 150) {
				state = Rotate;
			}
		break;

		// Segundo estado rotar siguiendo al jugador
		case Rotate:
			calculatePos();
			timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
			if (timeOffset >= 3) { state = Attack; timeOffset = 0; }
			break;

		// Me alargo
		case Attack:
			timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
			if (timeOffset >= 0.1) {
				tr->setWidth(50 + tr->getWidth());
				timeOffset = 0;
			}

			if (tr->getWidth() >= maxWidth) {
				state = Wait;
			}
			break;
		// Espero y me borro
		case Wait:
			timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
			if (timeOffset >= 1) { gObj->setAlive(false); }
			break;
	}
}

// Magia de vectores
void TargetedComponent::calculatePos() {
	// Calculo la direccion del tentaculo (posicion del jugador menos la del centro del boss con un margen de pixeles
	Vector2D dir = (pltr->getPos() - bossTr->getCenter()).normalize() * POINTER_DEFAULT_RADIUS * 2;
	// Seteo la posicion (suma del centro del boss mas su posicion inicial mas la direccion del tentaculo y menos la posicion actual
	tr->setPos(dir + bossTr->getCenter() + bossTr->getInitialPosition() - bossTr->getPos());
	// Roto el tentaculo
	tr->setRotation(Vector2D(1, 0).angle(dir.normalize()));
}