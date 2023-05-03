#include "TargetedComponent.h"
#include "../../gameObjects/GameObject.h"
#include "../../core/SDLApplication.h"

TargetedComponent::TargetedComponent(Transform* p, Transform* b) : 
	Component(), tr(nullptr), pltr(p), bossTr(b), state(0), timeOffset(0), maxWidth(600) { }

void TargetedComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
}

void TargetedComponent::update() {
	Vector2D dir;
	switch (state) {
		// primer estado: alargar el objeto
		case 0:
			calculatePos();
			timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
			if (timeOffset >= 0.1) {
				tr->setWidth(tr->getWidth() + 10);
				timeOffset = 0;
			}

			if (tr->getWidth() >= 150) {
				state = 1;
			}
		break;

		// Segundo estado rotar siguiendo al jugador
		case 1:
			calculatePos();
			timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
			if (timeOffset >= 3) { state = 2; timeOffset = 0; }
			break;

		// Me alargo
		case 2:
			timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
			if (timeOffset >= 0.1) {
				tr->setWidth(50 + tr->getWidth());
				timeOffset = 0;
			}

			if (tr->getWidth() >= maxWidth) {
				state = 3;
			}
			break;
		// Espero y me borro
		case 3:
			timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
			if (timeOffset >= 1) { gObj->setAlive(false); }
			break;
	}
}

void TargetedComponent::calculatePos() {
	Vector2D dir = (pltr->getPos() - bossTr->getCenter()).normalize() * 200;
	tr->setPos(dir + bossTr->getCenter() + bossTr->getInitialPosition() - bossTr->getPos());
	tr->setRotation(Vector2D(1, 0).angle(dir.normalize()));
}