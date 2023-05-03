#include "TentaclesPortalComponent.h"
#include "../../gameObjects/GameObject.h"
#include "../../core/SDLApplication.h"
#include "../General Components/Image.h"

TentaclesPortalComponent::TentaclesPortalComponent(Transform* b) :
	Component(), boss(b), tr(nullptr), tentDer(nullptr), tentIzq(nullptr), ti(nullptr), td(nullptr) {}

void TentaclesPortalComponent::initComponent() {
	state = 0;
	startRotation = false;
	timeOffset = 0;
	tr = gObj->getComponent<Transform>();
}

void TentaclesPortalComponent::update() {
	switch (state) {
	case 0:
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
		//Instancio los tentaculos
		if (timeOffset >= 0.25) {
			ti = gStt->addGameObject(_grp_ENM_ATTACK);
			tentIzq = ti->addComponent<Transform>(tr->getPos() + Vector2D(0, tr->getHeight() / 2 - 20), Vector2D(), 50, 40, 180);
			ti->addComponent<Image>(&sdlutils().images().at("BossTentacle"));
			ti->addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
				{
					player->getComponent<HealthComponent>()->receiveDamage(20);
				}
			);
			
			td = gStt->addGameObject(_grp_ENM_ATTACK);
			tentDer = td->addComponent<Transform>(tr->getPos() + Vector2D(tr->getWidth() - 45, tr->getHeight() / 2 - 20), Vector2D(), 50, 40);
			td->addComponent<Image>(&sdlutils().images().at("BossTentacle")); 
			td->addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
				{
					player->getComponent<HealthComponent>()->receiveDamage(20);
				}
			);
			state = 1;
			timeOffset = 0;
		}
		break;
	case 1:
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();

		// Los alargo
		if (timeOffset >= 0.1) {
			tentIzq->setWidth(tentIzq->getWidth() + 20);
			tentDer->setWidth(tentDer->getWidth() + 20);
			if (tentIzq->getWidth() >= 450 && tentDer->getWidth() >= 450) {
				state = 2;
			}
			timeOffset = 0;
		}
		break;

	case 2:
		// Rotamos los tres a la vez
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
		if (timeOffset >= 0.11) {
			calculatePos();
			tr->rotate(5);
			if (tr->getRotation() == 180) {
				state = 3;
			}
			timeOffset = 0;
		}
		break;
	case 3:
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
		if (timeOffset >= 1) { ti->setAlive(false); td->setAlive(false); gObj->setAlive(false); }
		break;
	}
}

void TentaclesPortalComponent::calculatePos() {
	Vector2D dir = Vector2D(1, 0).rotate(tentDer->getRotation()) * tr->getWidth()/2;
	tentDer->setPos(dir + boss->getCenter() -  Vector2D(0, tentDer->getHeight() / 2) + boss->getInitialPosition() - boss->getPos());
	tentDer->rotate(5);

	dir = Vector2D(-1, 0).rotate(tentIzq->getRotation()) * tr->getWidth() / 2;
	tentIzq->setPos(boss->getCenter() - Vector2D(0, tentIzq->getHeight() / 2) + boss->getInitialPosition() - boss->getPos() - dir);
	tentIzq->rotate(5);
}