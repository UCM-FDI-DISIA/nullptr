#include "TargetedTentacle.h"

void TargetedTentacle::initGameObject(Vector2D pos, Transform* player) {
	Transform* boss = addComponent<Transform>(pos, VECTOR_ZERO, 25, 50, 0);
	addComponent<TargetedComponent>(player);
	addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
		{
			player->getComponent<HealthComponent>()->receiveDamage(damage);
		}
	);
	addComponent<Image>(&sdlutils().images().at(BOSS_TENTACLE));
}