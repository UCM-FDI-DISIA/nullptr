#include "TargetedTentacle.h"

void TargetedTentacle::initGameObject(Vector2D pos, Transform* player, bool imagen) {
	Transform* boss = addComponent<Transform>(pos, VECTOR_ZERO, 25, 50, 0);
	addComponent<TargetedComponent>(player);
	if(!imagen)
	addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
		{
			player->getComponent<HealthComponent>()->receiveDamage(damage);
		}
	);
	if (imagen)
	{
		//addComponent<Animator>()->createAnim(BOSS_TENTACLE, BOSS_TENTACLE_ANIMATION);
		addComponent<Image>(&sdlutils().images().at(BOSS_TENTACLE));
	}

}