#include "BossTentacle.h"

void BossTentacle::initGameObject(Transform* boss) {
	Transform* ptr = addComponent<Transform>(boss->getCenter() - TENTACLES_PORTALS_OFFSET, Vector2D(), PORTALS_W, PORTALS_H);

	addComponent<Image>(&sdlutils().images().at("BossPortals"));
	addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
		{
			player->getComponent<HealthComponent>()->receiveDamage(5);
		}
	);

	TentaclesPortalComponent* tc = addComponent<TentaclesPortalComponent>(boss);
}