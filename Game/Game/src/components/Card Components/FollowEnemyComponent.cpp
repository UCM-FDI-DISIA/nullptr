#include "FollowEnemyComponent.h"
#include "../../scenes/GameState.h"
#include "../../core/SDLApplication.h"


Transform* FollowEnemyComponent::findClosestEnemy()
{
	vector<GameObject*> enemies = gStt->getEntitiesByGroup(_grp_ENEMIES);
	Transform* res = nullptr;
	if (enemies.size() > 0) {
		float minDistance = INT_MAX;
		float distance;
		for (GameObject* e : enemies) {
			distance = (tr->getCenter() - e->getComponent<Transform>()->getCenter()).magnitude();
			if (minDistance > distance) {
				minDistance = distance;
				res = e->getComponent<Transform>();
			}
		}
	}
	return res;
}

void FollowEnemyComponent::update() {
	if (followStartTime <= 0) {
		if (enemy == nullptr) enemy = findClosestEnemy();
		else {

			Vector2D vel = tr->getVel();
			tr->setVel(vel.rotate(vel.angle(enemy->getCenter() - tr->getCenter()) > 0 ? 0.25 : -0.25));
			tr->setRotation(Vector2D(1, 0).angle(tr->getVel()));

		}
	}
	followStartTime -= SDLApplication::instance()->getDeltaTimeSeconds();
}

void FollowEnemyComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
}
