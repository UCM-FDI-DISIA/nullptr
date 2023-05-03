#include "BossCone.h"
#include "../../components/General Components/Animator.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/HealthComponent.h"
#include "../../components/General Components/LifetimeComponent.h"

void BossCone::initGameObject(Vector2D pos, float rot) {
	addComponent<Transform>(pos, Vector2D(), CONE_WITDH, CONE_HEIGHT, rot);
	Animator* anim = addComponent<Animator>(&sdlutils().images().at(CONE_BOSS), CONE_WITDH / 2, CONE_HEIGHT / 2, 6, 1);
	anim->createAnim("Action", 0, 5, 5, 1);
	anim->play("Action");
	addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
		{
			player->getComponent<HealthComponent>()->receiveDamage(damage);
		}
	);

	addComponent<LifeTimeComponent>(CONE_ATTACK_DURATION);
}