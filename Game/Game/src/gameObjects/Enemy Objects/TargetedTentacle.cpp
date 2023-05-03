#include "TargetedTentacle.h"

void TargetedTentacle::initGameObject(Transform* player, Transform* boss) {

	Vector2D dir = (player->getPos() - boss->getCenter()).normalize() * POINTER_DEFAULT_RADIUS * 2;
	Vector2D initialPos = dir + boss->getCenter() + boss->getInitialPosition() - boss->getPos();
	float rot = Vector2D(1, 0).angle(dir.normalize());
	addComponent<Transform>(initialPos, Vector2D(), TENTACLE_INITIAL_W, TENTACLE_H, rot);
	addComponent<TargetedComponent>(player, boss);
	addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
		{
			player->getComponent<HealthComponent>()->receiveDamage(damage);
		}
	);
	addComponent<Image>(&sdlutils().images().at(BOSS_TENTACLE));
}