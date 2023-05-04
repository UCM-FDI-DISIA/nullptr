#include "TentacleBehaviour.h"
#include "../../gameObjects/GameObject.h"
#include "../../core/SDLApplication.h"

TentacleBehaviour::TentacleBehaviour(TentaclesPortalComponent* tpc,  bool mirror) : 
	Component(), portals(tpc), tr(nullptr), state(0), timeOffset(0), orientation(mirror) { }

void TentacleBehaviour::initComponent() {
	tr = gObj->getComponent<Transform>();
	maxWitdh = 300;
}

void TentacleBehaviour::update() {
	switch (state) {
		// Primer estado: cuento 2 segundos
	case 0:
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
		if (timeOffset >= 2) {
			state = 1; timeOffset = 0;
		}
		break;

		//Segundo estado, me alargo
	case 1: 
		{
			timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
			if (timeOffset >= 0.1) {
				if (orientation)
					tr->setWidth(tr->getWidth() + 20);
				else tr->setWidth(tr->getWidth() - 20);
				timeOffset = 0;
			}
			if (abs(tr->getWidth()) >= maxWitdh) {
				state = 2;
				timeOffset = 0;
			}
		}
		break;

		//Tercer estado, espero 1 segundo
	case 2:
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
		if (timeOffset >= 1) {
			state = 3; timeOffset = 0;
		}
		break;
		//Cuarto estado: roto 180 grados
	case 3:

		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
		if (timeOffset >= 0.5) {
			tr->rotate(22.5);
			timeOffset = 0;
		}

		if (tr->getRotation() >= 180) {
			state = 4;
			timeOffset = 0;
		}
		break;

		//Quinto estado: me borro
	case 5:
		gObj->setAlive(false);
		break;
	}
}