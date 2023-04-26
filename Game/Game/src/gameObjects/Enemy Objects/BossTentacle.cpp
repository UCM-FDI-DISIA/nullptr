#include "BossTentacle.h"

void BossTentacle:: initGameObject(Vector2D pos, bool mirror) {
	Transform* boss = addComponent<Transform>(pos, VECTOR_ZERO, 25, 50, mirror? 180 : 0);
	addComponent<TentacleBehaviour>(mirror);
	addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
		{
			player->getComponent<HealthComponent>()->receiveDamage(damage);
		}
	);
	addComponent<Image>(&sdlutils().images().at("BossTentacle"));
}