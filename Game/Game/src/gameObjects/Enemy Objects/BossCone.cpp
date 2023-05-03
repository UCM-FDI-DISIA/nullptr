#include "BossCone.h"
#include "../../components/General Components/Animator.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/HealthComponent.h"
#include "../../components/General Components/LifetimeComponent.h"

void BossCone::initGameObject(Vector2D pos, float rot) {
	addComponent<Transform>(pos, Vector2D(), 300, 180, rot);
	Animator* anim = addComponent<Animator>(&sdlutils().images().at(CONE_BOSS), 150, 90, 6, 1);
	anim->createAnim("Action", 0, 5, 5, 1);
	anim->play("Action");
	addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
		{
			player->getComponent<HealthComponent>()->receiveDamage(damage);
		}
	);

	addComponent<LifeTimeComponent>(2.5);
}