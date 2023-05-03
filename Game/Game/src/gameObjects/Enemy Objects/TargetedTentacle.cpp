#include "TargetedTentacle.h"

void TargetedTentacle::initGameObject(Transform* player, Transform* boss) {

	Vector2D dir = (player->getPos() - boss->getCenter()).normalize() * 200;
	Vector2D initialPos = dir + boss->getCenter() + boss->getInitialPosition() - boss->getPos();
	float rot = Vector2D(1, 0).angle(dir.normalize());
	addComponent<Transform>(initialPos, Vector2D(), 50, 40, rot);
	addComponent<TargetedComponent>(player, boss);
	addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
		{
			player->getComponent<HealthComponent>()->receiveDamage(damage);
		}
	);
	addComponent<Image>(&sdlutils().images().at("BossTentacle"));
}