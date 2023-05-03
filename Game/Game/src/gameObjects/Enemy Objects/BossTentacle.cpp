#include "BossTentacle.h"

void BossTentacle::initGameObject(Transform* boss) {
	Transform* ptr = addComponent<Transform>(boss->getCenter() - Vector2D(250, 100), Vector2D(), 500, 200);

	addComponent<Image>(&sdlutils().images().at("BossPortals"));
	addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
		{
			player->getComponent<HealthComponent>()->receiveDamage(5);
		}
	);

	TentaclesPortalComponent* tc = addComponent<TentaclesPortalComponent>(boss);
}