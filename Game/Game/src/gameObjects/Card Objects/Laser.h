#include "../GameObject.h"
#include "../../core/SDLApplication.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../components/Card Components/SwordSlashBehaviour.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/BulletBehavior.h"

class Laser : public GameObject {
public:
	void initGameObject(Vector2D pos, float rotation, int damage, grpId group) {
		addComponent<Transform>(pos, Vector2D(0,0), Vector2D(0, HEIGHT / 2), WIDTH, HEIGHT, rotation);
		addComponent<Image>(SDLApplication::getTexture("Laser"));
		addComponent<BulletBehavior>(damage);
		addComponent<ColliderComponent>(getComponent<BulletBehavior>()->bulletAttack(), group);
		addComponent<LifeTimeComponent>(0.08);
	}
private:
	const float HEIGHT = 10;
	const float WIDTH = 1100;
};